#include "BPosManager.h"
#include "constants.h"
#include "BKCconvert.h"
#include "DataManager.h"

#include <QThread>
#include <iostream>
#include <dlfcn.h>
#include <iconv.h>
#include <unistd.h>

//--------------------------------------------------------------------------------------------------
BPosManager::BPosManager(QObject *parent)
    : QObject (parent)
{
    //load BPOSLib
    m_lib = dlopen("libBPOSLib.so", RTLD_LAZY);
    if(!m_lib) {
        std::cout << "Cannot load library: " << dlerror() << std::endl;
        return;
    }
   init();
}
//--------------------------------------------------------------------------------------------------
BPosManager::~BPosManager()
{
    //destroy the instance of GTBClient
    destroyBPOSInstance(m_pBPOSClient);
    dlclose(m_lib);
}
//--------------------------------------------------------------------------------------------------
/*
 * Settlement (Z-report)
ECR Settlement
{STX} 0017REQ=SET;MID=BANK;{LRC}
POS Answer:
{STX}0039RESP=SET;RC=0000;MID=BANK;TID=12123123;BATCH=1;DEBAMT=1000;DEBNUM=2;
CRDAMT=2000;CRDNUM=1;CANAMT=200;CANNUM=1;TXNNUM=4
;{LRC}
 */
void BPosManager::onSendSettlment()
{
    std::cout << "\tSETTLMENT: " << std::endl;
    int rc = ECRC_OK;
    rc = m_pBPOSClient->CommClose();
    std::cout << "\tCommClose... OK" << std::endl;

    rc = m_pBPOSClient->CommOpenTCP(DefaultSettings::defaultIp.c_str(), DefaultSettings::defaultPort.c_str());

    unsigned char ucLastResult = 0;
    int lastResult = m_pBPOSClient->get_LastResult(ucLastResult);
    if (lastResult != 0) {
        char sError[ERROR_SIZE_MAX];
        m_pBPOSClient->get_LastErrorDescription(sError, ERROR_SIZE_MAX);
        std::cout << "\tERROR CommOpenTCP: " << std::string(sError) << std::endl;
        return;
    }

    std::cout << "\tCommOpenTCP opened" << std::endl;
    std::cout << "\tLastResult = " <<  static_cast<int>(ucLastResult) << std::endl;

    unsigned char merchantID = DataManager::getInstance()->getMerchantID();
    m_pBPOSClient->Settlement(merchantID);

    int counter = 0;
    unsigned char statusCode = 0;
    unsigned char lastStatusCode = 0;
    unsigned char ucLastRes = 2;
    char strLastStatMsgDescr[128] = {0};
    iconv_t d;
    d = iconv_open("UTF-8","CP1251");

    //int status = Status::BPOS_StatusNoStatus;
    while (counter != (Timeouts::RESPONSE_TIMEOUT / Timeouts::SLEEP)) {
        rc = m_pBPOSClient->get_LastStatMsgCode(statusCode);

        if (statusCode && (lastStatusCode != statusCode)) {
            lastStatusCode = statusCode;
            std::cout << "\tLastStatMsgCode = ";
            std::cout << static_cast<int>(statusCode) << std::endl;
        }

        char strVal[128];
        rc = m_pBPOSClient->get_LastStatMsgDescription(strVal, 128);
       // std::cout << "\tLastStatMsgDescription = ";
        if(statusCode && (strcmp(strLastStatMsgDescr, strVal))) {
            memcpy(strLastStatMsgDescr, strVal, sizeof(strVal));
            char sCP1251[ERROR_SIZE_MAX] 	= {0};
            Utf(strVal, sCP1251, d);
            std::cout << "\tLastStatMsgDescription = ";
            std::cout << sCP1251 << std::endl;
        }

        ucLastRes;
        m_pBPOSClient->get_LastResult(ucLastRes);
        if(ucLastRes != 2)
            break;

        counter++;
        QThread::msleep(Timeouts::SLEEP);
    }

    iconv_close(d);
    std::cout << "\tLast result = ";
    std::cout << static_cast<int>(ucLastRes) << std::endl;

    std::cout << "\tSETTLMENT FINISHED" << std::endl;
}
//--------------------------------------------------------------------------------------------------
/*
«Purchase».

The actions order:

    Open communication port (CommOpenTCP)
    Check result (LastResult). Continue if LastResult = 0.
    Send command Purchase with the amount of money.
    Check LastResult, LastErrorCode, LastStatMsgCode in the loop.
    If LastResult = 0 and LastErrorCode = 0, than purchase operation was successful. If not, we cannot continue operations.
    Send Confirm (if do not send confirmation, money return to the client's bank card).
    Request cheque if needed ReqCurrReceipt.
 */
void BPosManager::onSendPurchase()
{
    int rc = ECRC_OK;
    rc = m_pBPOSClient->CommClose();
    std::cout << "CommClose... OK" << std::endl;

    rc = m_pBPOSClient->CommOpenTCP(DefaultSettings::defaultIp.c_str(), DefaultSettings::defaultPort.c_str());

    unsigned char ucLastResult = 0;
    int lastResult = m_pBPOSClient->get_LastResult(ucLastResult);
    if (lastResult != 0) {
        char sError[ERROR_SIZE_MAX];
        m_pBPOSClient->get_LastErrorDescription(sError, ERROR_SIZE_MAX);
        std::cout << "ERROR CommOpenTCP: " << std::string(sError) << std::endl;
        return;
    }

    std::cout << "CommOpenTCP opened" << std::endl;
    std::cout << "LastResult = " <<  static_cast<int>(ucLastResult) << std::endl;

    unsigned int amount = DataManager::getInstance()->getAmount();
    unsigned int addAmount = 0;
    unsigned char merchantNdx = DataManager::getInstance()->getMerchantID();

    std::count << "PURCHASE AMOUNT " << amount;

    m_pBPOSClient->Purchase(amount, addAmount, merchantNdx);

    // in the cycle ask  LastResult, LastErrorCode, LastStatMsgCode
    int counter = 0;
    unsigned char statusCode = 0;
    unsigned char lastStatusCode = 0;
    unsigned char ucLastRes = 2;
    char strLastStatMsgDescr[128] = {0};
    iconv_t d;
    d = iconv_open("UTF-8","CP1251");


    int status = Status::BPOS_StatusNoStatus;
    while (counter != (Timeouts::RESPONSE_TIMEOUT / Timeouts::SLEEP)
           && DataManager::getInstance()->getCommand() == Command::BPOS_CmdPurchase) {

        rc = m_pBPOSClient->get_LastStatMsgCode(statusCode);

        switch (statusCode) {
            case BPosStatusCodes::not_available: { break; }
            case BPosStatusCodes::card_was_read: { status = Status::BPOS_StatusCardRead; break; }
            case BPosStatusCodes::used_chip_card: { break; }
            case BPosStatusCodes::authorization_in_progress: { break; }
            case BPosStatusCodes::waiting_for_cashier_action: { break; }
            case BPosStatusCodes::printing_receipt: { break; }
            case BPosStatusCodes::pin_entry_is_needed: { break; }
            case BPosStatusCodes::card_was_removed: { break; }
            case BPosStatusCodes::EMV_multi_aid: { break; }
            case BPosStatusCodes::waiting_for_card: { status = Status::BPOS_StatusWaittingCard; break; }
            case BPosStatusCodes::in_progress: { break; }
            case BPosStatusCodes::correct_transaction: { break; }
            case BPosStatusCodes::pin_input_wait_key: { break; }
            case BPosStatusCodes::pin_input_backspace_pressed: { break; }
            case BPosStatusCodes::pin_input_key_pressed: { break; }
        }

        DataManager::getInstance()->setStatus(status);

        if (statusCode && (lastStatusCode != statusCode)) {
            lastStatusCode = statusCode;
            std::cout << "\tLastStatMsgCode = ";
            std::cout << static_cast<int>(statusCode) << std::endl;
        }

        char strVal[128];
        rc = m_pBPOSClient->get_LastStatMsgDescription(strVal, 128);

        if(statusCode && (strcmp(strLastStatMsgDescr, strVal))) {
            memcpy(strLastStatMsgDescr, strVal, sizeof(strVal));
            char sCP1251[ERROR_SIZE_MAX] 	= {0};
            Utf(strVal, sCP1251, d);
            std::cout << "\tLastStatMsgDescription = ";
            std::cout << sCP1251 << std::endl;
        }

    //    ucLastRes;
        m_pBPOSClient->get_LastResult(ucLastRes);
        if(ucLastRes != 2)
            break;

        counter++;
        QThread::msleep(Timeouts::SLEEP);
    }

    int command = DataManager::getInstance()->getCommand();
    if (command == Command::BPOS_CmdCancelWaitting ) {
        // cancel current action
        DataManager::getInstance()->setStatus(Status::BPOS_StatusNoStatus);
        onSendCancel();
        m_isCancelFulfilled = true;
        return;
    }

    std::cout << "\Last result = ";
    std::cout << static_cast<int>(ucLastRes) << std::endl;

    // OK
    if (ucLastRes == 0) {
        std::cout << "\tCONFIRM PURCHASE OPERATION" << std::endl;
        m_pBPOSClient->Confirm(); // TODO: check result

        DataManager::getInstance()->setStatus(Status::BPOS_StatusPaidSuccessfuly);
        std::cout << "\tPURCHASE SUCCESSFUL" << std::endl;
            iconv_close(d);
        return;
    }


    if (ucLastRes == 1) {
        char sError[ERROR_SIZE_MAX];
        unsigned char lastErrorCode = 0;
        m_pBPOSClient->get_LastErrorCode(lastErrorCode);
        std::cout << "\tERROR CODE PURCHASE: " << static_cast<int>(lastErrorCode) << std::endl;
        if (lastErrorCode == 4) {
            DataManager::getInstance()->setStatus(Status::BPOS_StatusPaymentCanceledByTerminal);
        }

        m_pBPOSClient->get_LastErrorDescription(sError, ERROR_SIZE_MAX);
        //std::cout << "\tERROR PURCHASE: " << std::string(sError) << std::endl;
        memcpy(strLastStatMsgDescr, sError, sizeof(sError));
        char sCP1251[ERROR_SIZE_MAX] 	= {0};
        Utf(sError, sCP1251, d);
        std::cout << "\tERROR PURCHASE: = ";
        std::cout << sCP1251 << std::endl;
    }

    iconv_close(d);
}
//--------------------------------------------------------------------------------------------------
/*
 * Cancel(void)
Cancels fulfilling the operation in case LastResult returns 2.
 */
void BPosManager::onSendCancel()
{
    // that command was sent on the function onSendPurchase
    if (m_isCancelFulfilled) {
        m_isCancelFulfilled = false;
        return;
    }

    std::cout << "\tCANCEL: " << std::endl;
    int rc = ECRC_OK;
    rc = m_pBPOSClient->CommClose();
    std::cout << "\tCommClose... OK" << std::endl;

    rc = m_pBPOSClient->CommOpenTCP(DefaultSettings::defaultIp.c_str(), DefaultSettings::defaultPort.c_str());

    unsigned char ucLastResult = 0;
    int lastResult = m_pBPOSClient->get_LastResult(ucLastResult);
    if (lastResult != 0) {
        char sError[ERROR_SIZE_MAX];
        m_pBPOSClient->get_LastErrorDescription(sError, ERROR_SIZE_MAX);
        std::cout << "\tERROR CommOpenTCP: " << std::string(sError) << std::endl;
        return;
    }

    std::cout << "\tCommOpenTCP opened" << std::endl;
    std::cout << "\tLastResult = " <<  static_cast<int>(ucLastResult) << std::endl;

    m_pBPOSClient->Cancel();

    int counter = 0;
    unsigned char statusCode = 0;
    unsigned char lastStatusCode = 0;
    unsigned char ucLastRes = 2;
    char strLastStatMsgDescr[128] = {0};
    iconv_t d;
    d = iconv_open("UTF-8","CP1251");

   // int status = Status::BPOS_StatusNoStatus;
    while (counter != (Timeouts::RESPONSE_TIMEOUT / Timeouts::SLEEP)) {
        rc = m_pBPOSClient->get_LastStatMsgCode(statusCode);

        lastStatusCode = statusCode;
        std::cout << "\tLastStatMsgCode = ";
        std::cout << static_cast<int>(statusCode) << std::endl;

        char strVal[128];
        rc = m_pBPOSClient->get_LastStatMsgDescription(strVal, 128);

        if(statusCode && (strcmp(strLastStatMsgDescr, strVal))) {
            memcpy(strLastStatMsgDescr, strVal, sizeof(strVal));
            char sCP1251[ERROR_SIZE_MAX] 	= {0};
            Utf(strVal, sCP1251, d);
            std::cout << "\tLastStatMsgDescription = ";
            std::cout << sCP1251 << std::endl;
        }

        //ucLastRes;
        m_pBPOSClient->get_LastResult(ucLastRes);
        if(ucLastRes != 2)
            break;

        counter++;
        QThread::msleep(Timeouts::SLEEP);
    }

    iconv_close(d);
    std::cout << "\tLast result = ";
    std::cout << static_cast<int>(ucLastRes) << std::endl;

    std::cout << "\tCANCEL FINISHED" << std::endl;
}
//--------------------------------------------------------------------------------------------------
void BPosManager::onSendCommand2PayPas(int command)
{
    if (m_pBPOSClient == nullptr) {
        std::cout << "m_pBPOSClient was not created" << std::endl;
        return;
    }

    std::cout << "\tCOMMAND: " << std::hex << command << std::endl;

    switch (command) {
        case Command::BPOS_CmdNoCommand: {
            return; //break;
        }
        case Command::BPOS_CmdPurchase: {
            onSendPurchase();
            break;
        }
        case Command::BPOS_CmdCancelWaitting:// {
            //return; // break;
        //}
        case Command::BPOS_CmdCancel: {
            onSendCancel();
            break;
        }
        case Command::BPOS_CmdConfirm: {
            return; //break;
        }
        case Command::BPOS_CmdSettlement: {
            onSendSettlment();
            break;
        }
        default: return;//break;
    }
}
//--------------------------------------------------------------------------------------------------
void BPosManager::init()
{
    if(!m_lib) {
        std::cout << "library wasnot loaded: " << dlerror() << std::endl;
        return;
    }

    //reset errors
    dlerror();

    create_t* creatBPOSInstance = (create_t*)dlsym(m_lib, "create");
    const char* dlsym_error = dlerror();
    if(dlsym_error) {
        std::cout << "Cannot load symbol create: " << dlsym_error << std::endl;
        return;
    }

    destroyBPOSInstance = (destroy_t*) dlsym(m_lib, "destroy");
        dlsym_error = dlerror();
        if(dlsym_error) {
            std::cout << "Cannot load symbol destroy: " << dlsym_error << std::endl;
            return;
        }

    m_pBPOSClient = creatBPOSInstance();

    std::cout << "useLogging()..." << std::endl;
    m_pBPOSClient->useLogging(2, "logbpos.txt");

    std::cout << "SetErrorLang...." << std::endl;
    m_pBPOSClient->SetErrorLang(DefaultSettings::defErrorLang);
}
//--------------------------------------------------------------------------------------------------
