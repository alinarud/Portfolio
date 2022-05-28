#ifndef BPOSMANAGER_H
#define BPOSMANAGER_H

#include <QObject>
#include <ctime>
#include "BPOSClient.h"
#include "constants.h"

class BPosManager : public QObject
{
    Q_OBJECT
public:
    BPosManager(QObject *parent = nullptr);
    ~BPosManager();

public slots:
    void onSendSettlment();
    void onSendPurchase();
    void onSendCancel();
    void onSendCommand2PayPas(int command);

private:
    void init();

private:
    void* m_lib = nullptr;
    CBPOSClient *m_pBPOSClient = nullptr;
    destroy_t* destroyBPOSInstance = nullptr;
    bool m_isError = false;
    bool m_isCancelFulfilled = false;
};

#endif // BPOSMANAGER_H
