#ifndef SERIALPORT_H
#define SERIALPORT_H


#include <stdio.h>
#include <string.h>
#include <QTimer>
#include <QObject>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

class SerialPort : public QObject
{
    Q_OBJECT
public:
    SerialPort(QObject *parent = nullptr);
    virtual ~SerialPort();

    void writeMessage(char *msg, int len);
    void readData();
    void closeSerialPort();

private slots:
    void onReadTimeout();
    void onStopReadingProcess();

private:
    void openSerialPort();
    std::vector<unsigned char> getReadPackage(const char *data, int len);
    std::vector<std::vector<unsigned char>> getPackage(std::vector<unsigned char> data);
    void setSerialPortConfigurations();
    void readHoldingRegistersReceived(std::vector<unsigned char> data);
    void presetSingleRegisterReceived(std::vector<unsigned char> data);
    void presetMultipleRegsReceived(std::vector<unsigned char> data);
    int getCRC(char *data, int len);
    void startReadingProcess();
    bool checkCRC(std::vector<unsigned char> data);
    void setRegisterData(int regAddress, unsigned char byteHi, unsigned char byteLo);

private:
    int m_serial_port = -1;
    bool m_isRead;
    QTimer *m_readTimer;
};

#endif // SERIALPORT_H
