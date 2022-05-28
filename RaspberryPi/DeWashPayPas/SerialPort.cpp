#include "SerialPort.h"
#include "constants.h"
#include "DataManager.h"

#include <iostream>
#include <QThread>
#include <vector>
#include <wiringPi.h>

//--------------------------------------------------------------------------------------------------
SerialPort::SerialPort(QObject *parent) : QObject (parent)
{
    std::cout << "Serial port initialization" << std::endl;

    wiringPiSetup();     // init wirinPi
    pinMode(1, OUTPUT);  // set GPIO_GEN1 (12 physical) wPi - 1 in OUTPUT
    digitalWrite(1, 0); // default 0 - read data

    m_readTimer = new QTimer(this);
    m_readTimer->setInterval(10);

    QObject::connect(m_readTimer, &QTimer::timeout, this, &SerialPort::onReadTimeout);

    openSerialPort();
}
//--------------------------------------------------------------------------------------------------
SerialPort::~SerialPort()
{
    m_readTimer->stop();
    closeSerialPort();

    std::cout << "Serial port destructor" << std::endl;
}
//--------------------------------------------------------------------------------------------------
void SerialPort::closeSerialPort()
{
    close(m_serial_port);
    std::cout << "Serial port was closed" << std::endl;
}
//--------------------------------------------------------------------------------------------------
void SerialPort::onReadTimeout()
{
    readData();
}
//--------------------------------------------------------------------------------------------------
void SerialPort::onStopReadingProcess()
{
    m_readTimer->stop();
}
//--------------------------------------------------------------------------------------------------
void SerialPort::openSerialPort()
{
    m_serial_port = open("/dev/serial0", O_RDWR);

    // Check for errors
    if (m_serial_port < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        // if the error 13
        // $ sudo adduser $USER dialout
        // newgrp dialout
        return;
    }

    std::cout << "Serial post /dev/serial0 was opened" << std::endl;

    // set serial port configuration
    setSerialPortConfigurations();

    startReadingProcess();
}
//--------------------------------------------------------------------------------------------------
std::vector<unsigned char> SerialPort::getReadPackage(const char *data, int len)
{
    std::vector<unsigned char> tmp;
    // try to find slave address in the received package
    for (int i = 0; i < len; i++) {
        int value = static_cast<int>(data[i]);
        if (value == Constants::SLAVE_ADDRESS) {
            for (int j = i; j < len; j++) {
                unsigned char val = data[j];
                tmp.push_back(val);
            }
            break;
        }
    }

    // now check modbus package
    if (tmp.size() < DefaultSettings::minPackageLenght) {
        std::cout << "\tPACKAGE ERROR: invalid package size" << std::endl;
        return std::vector<unsigned char> ();
    }

    // ckeck slave address
    short int slaveAddress = tmp[eSlaveAddress];
    if (slaveAddress != Constants::SLAVE_ADDRESS) {
        std::cout << "\tPACKAGE ERROR: slave address is invalid" << std::endl;
        return std::vector<unsigned char>();
    }

    // check lenght
    if (tmp.size() > DefaultSettings::minPackageLenght) {
        // ePresetMultipleRegStruct check byte counter and size after it
        int counter = static_cast<int>(data[ePMBytesCounter]);
        if ((counter + DefaultSettings::crcLenght) != (tmp.size() - (ePMBytesCounter + 1))) {
            std::cout << "\tPACKAGE ERROR: lenght for function preset_multiple_register is invalid" << std::endl;
            return std::vector<unsigned char>();
        }
    }

    int newLen = tmp.size();
    //check CRC
    if (!checkCRC(tmp)) {
        return std::vector<unsigned char>();
    }

    return tmp;
}
//--------------------------------------------------------------------------------------------------
void SerialPort::setSerialPortConfigurations()
{
    if (m_serial_port < 0)
        return;

    // Create new termios struc, we call it 'tty' for convention
    struct termios tty;
    memset(&tty, 0, sizeof tty);

    // Read in existing settings, and handle any error
    if(tcgetattr(m_serial_port, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }

    // parameters
    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag |= CS8; // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
    tty.c_lflag &= ~ICANON; // Disable canonical mode (In canonical mode, input is processed when a new line character is received)
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
    tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 9600
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    // Save tty settings, also checking for error
    if (tcsetattr(m_serial_port, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }
}
//--------------------------------------------------------------------------------------------------
void SerialPort::writeMessage(char *msg, int len)
{
    digitalWrite(1, 1); // set 1 - write data
    write(m_serial_port, msg, len);

    QThread::msleep(50);
    digitalWrite(1, 0); // set 0 - read data

    std::cout << "RESPONSE ";
    for (int i = 0; i < len; i++) {
        std::cout << (int)msg[i] << " ";
    }

    std::cout << std::endl << std::endl;
}
//--------------------------------------------------------------------------------------------------
void SerialPort::readData()
{
    char read_buf[32];
    memset(&read_buf, '\0', sizeof(read_buf));

    long int n = read(m_serial_port, read_buf, sizeof(read_buf));

    if (n <= 0) {
        return;
    }

    // maybe sth left in the buffer
    QThread::msleep(150); // wait 300 ms for any data
    char tmp_buf[32];
    memset(&tmp_buf, '\0', sizeof(tmp_buf));
    long int a = read(m_serial_port, tmp_buf, sizeof(tmp_buf));

    int len = n + a;
    // package too short
    if (len < DefaultSettings::minPackageLenght) {
        return;
    }

    char res_buf [len];
    for (int i = 0; i < n; i++) {
        res_buf[i] = read_buf[i];
    }

    int ndx = 0;
    for (int i = n; i < n + a; i++) {
        res_buf[i] = tmp_buf[ndx];
        ndx++;
    }

    std::vector<unsigned char> package = getReadPackage(res_buf, len);
    if (package.size() < DefaultSettings::minPackageLenght) {
        return;
    }

    std::cout << "RECEIVED: " << len << " bytes: ";
    for (int i = 0; i < len; i++) {
        std::cout << std::hex << static_cast<int>(res_buf[i]) << " ";
    }

    std::cout << std::endl;

    short int function = package[eFunctionNumber];
     switch (function) {
         case FunctionAddress::FUNC_PRESET_MULTIPLE_REGS: {
             presetMultipleRegsReceived(package);
             break;
         }
         case FunctionAddress::FUNC_PRESET_SINGLE_REGISTER: {
             presetSingleRegisterReceived(package);
             break;
         }
         case FunctionAddress::FUNC_READ_HOLDING_REGISTERS: {
             readHoldingRegistersReceived(package);
             break;
         }
     }
}
//--------------------------------------------------------------------------------------------------
std::vector<std::vector<unsigned char> > SerialPort::getPackage(std::vector<unsigned char> data)
{
    std::vector<std::vector<unsigned char> > lstResult; // can be more than 1 package

    // find and check slave address
    short int slaveAddress = data[eSlaveAddress];
    if (slaveAddress != Constants::SLAVE_ADDRESS) {
        data.erase(data.begin());
        // try to find SLAVE addr and delete wrong
        for (int i = 0; i < data.size(); i++) {
            short int slaveAddress = data.at(eSlaveAddress);
            if (slaveAddress != Constants::SLAVE_ADDRESS) {
                data.erase(data.begin());
                continue;
            }

            break;
        }
    }

    // now check modbus package
    if (data.size() < DefaultSettings::minPackageLenght) {
        std::cout << "\tPACKAGE ERROR: invalid package size" << std::endl;
        return lstResult;
    }

    // get function number
    short int function = data.at(eFunctionNumber);
    if (function == FunctionAddress::FUNC_READ_HOLDING_REGISTERS
            || function == FunctionAddress::FUNC_PRESET_SINGLE_REGISTER) {

        // there is only one package
        if (data.size() == DefaultSettings::minPackageLenght) {
            lstResult.push_back(data);
            return lstResult;
        }

        // few packages
        // first lenght 8 - bits
        std::vector<unsigned char> tmp;
        for (int i = 0; i < DefaultSettings::minPackageLenght; ++i) {
            tmp.push_back(data.at(i));
        }
        lstResult.push_back(tmp);
        data.erase(data.begin(), data.begin() + DefaultSettings::minPackageLenght);

        // next step - find slave
        std::vector<std::vector<unsigned char>> tmpLst = getPackage(data);
        for (int i = 0; i < tmpLst.size(); ++i) {
            lstResult.push_back(tmpLst.at(i));
        }
        return lstResult;
    }

    if (function == FunctionAddress::FUNC_PRESET_MULTIPLE_REGS) {
        int counter = static_cast<int>(data[ePMBytesCounter]);

        if ((counter + DefaultSettings::crcLenght) != (data.size() - (ePMBytesCounter + 1))) {
            std::cout << "\tPACKAGE ERROR: lenght for function preset_multiple_register is invalid" << std::endl;
            return lstResult;
        }

        int explen = ePMBytesCounter + counter + DefaultSettings::crcLenght;
        if (data.size() == explen) {
            lstResult.push_back(data);
            return lstResult;
        }

        // few packages
        std::vector<unsigned char> tmp;
        for (int i = 0; i < explen; ++i) {
            tmp.push_back(data.at(i));
        }
        lstResult.push_back(tmp);
        data.erase(data.begin(), data.begin() + explen);

        // next step - find slave
        std::vector<std::vector<unsigned char>> tmpLst = getPackage(data);
        for (int i = 0; i < tmpLst.size(); ++i) {
            lstResult.push_back(tmpLst.at(i));
        }
        return lstResult;
    }

    return lstResult;
}
//--------------------------------------------------------------------------------------------------
void SerialPort::readHoldingRegistersReceived(std::vector<unsigned char> data)
{
    int len = data.size();
    if (len <= eRHCRCLow) {
        return;
    }

    std::cout << "\tFUNCTION HOLDING_REGISTERS" << std::endl;

    int registerAddressByte1 = data[eRHStartAddrHigh];
    int registerAddressByte2 = data[eRHStartAddrLow];
    int startAddress = (registerAddressByte1 & 0xFF) | (registerAddressByte2 & 0xFF);

    int countByte1 = data[eRHRegsCountHigh];
    int countByte2 = data[eRHRegsCountLow];
    int countRegisters = (countByte1 & 0xFF) | (countByte2 & 0xFF);

    // fill response
    int responseSize = 4 + startAddress + countRegisters;
    char response[responseSize];
    response[eSlaveAddress] = Constants::SLAVE_ADDRESS;
    response[eFunctionNumber] = FunctionAddress::FUNC_READ_HOLDING_REGISTERS;
    response[eRHRBytesCounter] = static_cast<char>(countRegisters * 2);

    int ndx = eRHRDataHigh;
    for (int i = eRHRBytesCounter; i < (eRHRBytesCounter + countRegisters); i++) {
        //short int value = DataManager::getInstance()->getRegisterValue(startAddress);
        response[ndx] = DataManager::getInstance()->getRegisterHiValue(startAddress); //value >> 8;
        response[ndx + 1] = DataManager::getInstance()->getRegisterLoValue(startAddress); //static_cast<char>(value);

        ndx += 2;
        startAddress++;
    }

    int crc = getCRC(response, len);
    response[ndx] = static_cast<char>(crc >> 8);
    response[ndx + 1] = static_cast<char>(crc);

    writeMessage(response, ndx + 2);
}
//--------------------------------------------------------------------------------------------------
void SerialPort::presetSingleRegisterReceived(std::vector<unsigned char> data)
{
    int len = data.size();
    if (len <= eRHCRCLow) {
        return;
    }

    std::cout << "\tFUNCTION PRESET_SINGLE_REGISTER" << std::endl;
    int registerAddressByte1 = data[ePSStartAddrHigh];
    int registerAddressByte2 = data[ePSStartAddrLow];
    int registerAddress = (registerAddressByte1 & 0xFF) | (registerAddressByte2 & 0xFF);

    unsigned char byteHi = static_cast<unsigned char>(data[ePSDataHigh]);
    unsigned char byteLo = static_cast<unsigned char>(data[ePSDataLow]);

     // SET DATA
    setRegisterData(registerAddress, byteHi, byteLo);

    // SEND THE SAME RESPONSE
    char response[len];
    for (int i = 0; i < len; ++i) {
        response[i] = data.at(i);
    }

    writeMessage(response, len);
}
//--------------------------------------------------------------------------------------------------
void SerialPort::presetMultipleRegsReceived(std::vector<unsigned char> data)
{
    int len = data.size();
    std::cout << "\tFUNCTION MULTIPLE_REGISTERS" << std::endl;

    int registerAddressByte1 = (len > (ePMStartAddrHigh + 1)) ? data[ePMStartAddrHigh] : 0;
    int registerAddressByte2 = (len > (ePMStartAddrLow + 1)) ? data[ePMStartAddrLow] : 0;
    int startAddress = (registerAddressByte1 & 0xFF) | (registerAddressByte2 & 0xFF);

    int countByte1 = (len > (ePMRegsCountHigh + 1)) ? data[ePMRegsCountHigh] : 0;
    int countByte2 = (len > (ePMRegsCountLow + 1)) ? data[ePMRegsCountLow] : 0;
    int countRegisters = (countByte1 & 0xFF) | (countByte2 & 0xFF);

    int ndx = ePMDataHigh;
    int regAddress = startAddress;
    for (int i = 0; i < countRegisters; i++) {
        unsigned char byteHi = (len > (ndx + 1)) ? static_cast<unsigned char>(data[ndx]) : 0;
        unsigned char byteLo = (len > (ndx + 2)) ? static_cast<unsigned char>(data[ndx + 1]) : 0;
        setRegisterData(regAddress, byteHi, byteLo);

        ndx += 2;
        regAddress++;
    }

    char response[ePMRCount];
    response[eSlaveAddress] = Constants::SLAVE_ADDRESS;
    response[eFunctionNumber] = FunctionAddress::FUNC_PRESET_MULTIPLE_REGS;
    response[ePMRStartAddrHigh] = static_cast<char>(startAddress >> 8);
    response[ePMRStartAddrLow] = static_cast<char>(startAddress);
    response[ePMRRegsCountHigh] = static_cast<char>(countRegisters >> 8);
    response[ePMRRegsCountLow] = static_cast<char>(countRegisters);

    int crc = getCRC(response, ePMRRegsCountLow + 1);
    response[ePMRCRCHigh] = static_cast<char>(crc >> 8);
    response[ePMRCRCLow] = static_cast<char>(crc);

    writeMessage(response, ePMRCount);
}
//--------------------------------------------------------------------------------------------------
int SerialPort::getCRC(char *data, int len)
{
    int iPos = 0; // loop position in input buffer
    int crc = 0xFFFF;

    while (iPos < len) {
        crc ^= (data[iPos] & 0xFF);
        iPos++;
        for (int j = 0; j < 8; j++) {
            bool bitOne = ((crc & 0x1) == 0x1);
            crc >>= 1;
            if (bitOne) {
                crc ^= 0x0000A001;
            }
        }
    }

    return crc;
}
//--------------------------------------------------------------------------------------------------
void SerialPort::startReadingProcess()
{
    m_readTimer->start();
}
//--------------------------------------------------------------------------------------------------
bool SerialPort::checkCRC(std::vector<unsigned char> data)
{
    int temp_CRC = 0xffff;
    int temp_Flag;

    int len = data.size();
    for(int i = 0; i < (len - 2); i++) {
        int value = data[i];
        temp_CRC = temp_CRC ^ (value & 0xFF);

        for(int j = 0; j < 8; j++) {
            temp_Flag = temp_CRC;
            temp_CRC = temp_CRC >> 1;

            if((temp_Flag & 0x01) == 1) {
                temp_CRC = temp_CRC ^ 0xa001;
            }
        }
    }

    int crcByteLo = temp_CRC & 0xFF;
    int crcByteHi = (temp_CRC >> 8) & 0xFF;

    // Quantity of Registers
    int crcByte1 = data[len - 2];
    int crcByte2 = data[len - 1];
    int crc1 = crcByte1 & 0xFF;
    int crc2 = crcByte2 & 0xFF;

    if (crc1 != crcByteLo || crc2 != crcByteHi) {
        std::cout << "ERROR: wrong CRC" << std::endl;
        return false;
    }

    return true;
}
//--------------------------------------------------------------------------------------------------
void SerialPort::setRegisterData(int regAddress, unsigned char byteHi, unsigned char byteLo)
{
    switch (regAddress) {
        case eStatusReg: {
            DataManager::getInstance()->setStatus(byteHi, byteLo);
            break;
        }
        case eCommandReg: {
            DataManager::getInstance()->setCommand(byteHi, byteLo);
            break;
        }
        case eFirstCreditReg: {
            DataManager::getInstance()->setAmountReg17(byteHi, byteLo);
            break;
        }
        case eLastCreditReg: {
            DataManager::getInstance()->setAmountReg18(byteHi, byteLo);
            break;
        }
        default: break;
    }
}
//--------------------------------------------------------------------------------------------------
