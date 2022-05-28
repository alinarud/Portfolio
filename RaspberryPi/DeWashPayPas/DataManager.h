#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <vector>
#include "Data.h"
#include "BPosManager.h"

class DataManager : public QObject
{
    Q_OBJECT
protected:
    DataManager(QObject *parent = nullptr);
    ~DataManager();

public:
    static DataManager *getInstance();
    static void    shut();

    unsigned char getRegisterHiValue(int regAddress) const;
    unsigned char getRegisterLoValue(int regAddress) const;
    unsigned char getMerchantID() const;
    unsigned short int getStatus() const;
    unsigned short int getCommand() const;
    unsigned int getAmount() const;
    void setStatus(unsigned short int status);
    void setStatus(unsigned char byteHi, unsigned char byteLo);
    void setCommand(unsigned char byteHi, unsigned char byteLo);
    void setAmountReg17(unsigned char byteHi, unsigned char byteLo);
    void setAmountReg18(unsigned char byteHi, unsigned char byteLo);

    void resetData();

private:
    void registerValueUpdated(int regAddress, int value);

signals:
    void sendCommand2PayPas(int command);

private:
    static  DataManager    *m_dataManager;
    BPosManager            *m_bposManager;
    Data                    m_data;

};

#endif // DATAMANAGER_H
