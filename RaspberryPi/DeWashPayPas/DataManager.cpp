#include "DataManager.h"

DataManager * DataManager::m_dataManager;

//--------------------------------------------------------------------------------------------------
DataManager::DataManager(QObject *parent) : QObject(parent)
{
    m_bposManager = new BPosManager();

    m_data.amount = 0;
    m_data.command = 0;
    m_data.status = 0;

    connect(this, &DataManager::sendCommand2PayPas, m_bposManager, &BPosManager::onSendCommand2PayPas, Qt::QueuedConnection);
}
//--------------------------------------------------------------------------------------------------
DataManager::~DataManager()
{
    delete m_bposManager;
    m_bposManager = nullptr;
}
//--------------------------------------------------------------------------------------------------
DataManager *DataManager::getInstance()
{
    if (m_dataManager == nullptr)
           m_dataManager = new DataManager();
       return m_dataManager;
}
//--------------------------------------------------------------------------------------------------
void DataManager::shut()
{
    if (m_dataManager) {
        delete m_dataManager;
        m_dataManager = nullptr;
    }
}
//--------------------------------------------------------------------------------------------------
unsigned char DataManager::getRegisterHiValue(int regAddress) const
{
    switch (regAddress) {
        case eStatusReg: {
            return m_data.reg10.byteLo.l;
        }
        case eCommandReg: {
            return m_data.reg12.byteLo.l;
        }
        case eFirstCreditReg: {
            return m_data.reg17.byteLo.l;
        }
        case eLastCreditReg: {
            return m_data.reg18.byteLo.l;
        }
        default: break;
    }

    return 0;
}
//--------------------------------------------------------------------------------------------------
unsigned char DataManager::getRegisterLoValue(int regAddress) const
{
    switch (regAddress) {
        case eStatusReg: {
            return m_data.reg10.byteHi.h;
        }
        case eCommandReg: {
            return m_data.reg12.byteHi.h;
        }
        case eFirstCreditReg: {
            return m_data.reg17.byteHi.h;
        }
        case eLastCreditReg: {
            return m_data.reg18.byteHi.h;
        }
        default: break;
    }

    return 0;
}
//--------------------------------------------------------------------------------------------------
unsigned char DataManager::getMerchantID() const
{
    return 1;
}
//--------------------------------------------------------------------------------------------------
unsigned short DataManager::getStatus() const
{
    return m_data.status;
}
//--------------------------------------------------------------------------------------------------
unsigned short DataManager::getCommand() const
{
    return m_data.command;
}
//--------------------------------------------------------------------------------------------------
unsigned int DataManager::getAmount() const
{
    return m_data.amount;
}
//--------------------------------------------------------------------------------------------------
void DataManager::setStatus(unsigned short int status)
{
    if (m_data.status == status)
        return;

    m_data.status = status;
    std::cout << "\tSET STATUS: " << status << std::endl;
}
//--------------------------------------------------------------------------------------------------
void DataManager::setStatus(unsigned char byteHi, unsigned char byteLo)
{
    m_data.reg10.byteHi.h = byteLo;
    m_data.reg10.byteLo.l = byteHi;
    std::cout << "\tSET STATUS: " << m_data.status << std::endl;
}
//--------------------------------------------------------------------------------------------------
void DataManager::setCommand(unsigned char byteHi, unsigned char byteLo)
{
    m_data.reg12.byteHi.h = byteLo;
    m_data.reg12.byteLo.l = byteHi;
    std::cout << "\tSET COMMAND: " << (int)byteHi << ";" << (int)byteLo << ";" << m_data.command << std::endl;

    emit sendCommand2PayPas(m_data.command);
}
//--------------------------------------------------------------------------------------------------
void DataManager::setAmountReg17(unsigned char byteHi, unsigned char byteLo)
{
    m_data.reg17.byteHi.h = byteLo;
    m_data.reg17.byteLo.l = byteHi;
}
//--------------------------------------------------------------------------------------------------
void DataManager::setAmountReg18(unsigned char byteHi, unsigned char byteLo)
{
    m_data.reg18.byteHi.h = byteLo;
    m_data.reg18.byteLo.l = byteHi;

    std::cout << "\tSET AMOUNT: " << m_data.amount << std::endl;
}
//--------------------------------------------------------------------------------------------------
void DataManager::resetData()
{
    m_data.amount = 0;
    m_data.command = 0;
    m_data.status = 0;
}
//--------------------------------------------------------------------------------------------------
void DataManager::registerValueUpdated(int regAddress, int value)
{
    switch (regAddress) {
        case eCommandReg: {
            emit sendCommand2PayPas(value);
            break;
        }
        default:
            break;
    }
}
//--------------------------------------------------------------------------------------------------
