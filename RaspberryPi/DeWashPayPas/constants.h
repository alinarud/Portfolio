#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>

namespace DefaultSettings {
    const std::string defaultPort = "2100";
    const std::string defaultIp = "10.1.1.2";
    const int defaultMerchant = 1;
    const int defaultAmount = 1000;
    const int defErrorLang = 0;
    const int minPackageLenght = 8;
    const int crcLenght = 2;
}

namespace Timeouts {
    const int RESPONSE_TIMEOUT = 100000;
    const int SLEEP = 50;
}

namespace Constants {
    const short int SLAVE_ADDRESS = 7;
}

namespace FunctionAddress {
    const short int FUNC_READ_HOLDING_REGISTERS = 3;
    const short int FUNC_PRESET_SINGLE_REGISTER = 6;
    const short int FUNC_PRESET_MULTIPLE_REGS   = 16;
}

enum eHeaderStucture {
    eSlaveAddress = 0,
    eFunctionNumber = 1
};

enum eReadHoldingRegStruct {
    eRHStartAddrHigh = 2,
    eRHStartAddrLow = 3,
    eRHRegsCountHigh = 4,
    eRHRegsCountLow = 5,
    eRHCRCHigh = 6,
    eRHCRCLow = 7
};

enum eReadHoldingRegResponse {
    eRHRBytesCounter = 2,
    eRHRDataHigh = 3,
    eRHRDataLow = 4,
};

enum ePresetSingleRegStruct {
    ePSStartAddrHigh = 2,
    ePSStartAddrLow = 3,
    ePSDataHigh = 4,
    ePSDataLow = 5,
    ePSCRCHigh = 6,
    ePSCRCLow = 7
};

enum ePresetMultipleRegStruct {
    ePMStartAddrHigh = 2,
    ePMStartAddrLow = 3,
    ePMRegsCountHigh = 4,
    ePMRegsCountLow = 5,
    ePMBytesCounter = 6,
    ePMDataHigh = 7,
    ePMDataLow = 8
};


enum ePresetMultipleRegResponse {
    ePMRStartAddrHigh = 2,
    ePMRStartAddrLow = 3,
    ePMRRegsCountHigh = 4,
    ePMRRegsCountLow = 5,
    ePMRCRCHigh = 6,
    ePMRCRCLow = 7,
    ePMRCount = 8
};


enum eCommand
{
    Purchase = 1,
    Settlement,
    PrintBatchTotals,
    Confirm,
    Get_Receipt,
    Get_Receipt_ByInv,
    Refund,
    Void = 8,
    Cancel,
    GetTxnNum,
    GetTxnDataByOrder,
    GetTxnDataByInv,
    GetBatchTotals,
    CheckConnection,
    PrintLastSettleCopy,
    PrintBatchJournal,
    PurchaseService,
    IdentifyCard,
    SetErrorLang,
    SetControlMode,
    ReadKey,
    DisplayText,
    SetLine,
    ExchangeStatuses,
    Completion,
    ReadCard,
    Balance,
    Deposit,
    POSGetInfo,
    POSExTransaction,
    useSelectApp,
    StartScenario,
    SetExtraPrintData,
    SetExtraXmlData,
    useLogging,
    SendFile,
    SetScreen
};

enum
{
    DATA_SIZE_MAX	= 4096,
    ERROR_SIZE_MAX	= 128,
    RRN_SIZE		= 12+1
};


static const char* gBPOSLibTestError[] = {
        "RRN is to long",
        "System error"
};


enum eRegisters {
    eFirstMerchantReg   = 0x0000,
    eLastMerchantReg    = 0x0003,
    eStatusReg          = 0x0010, // - status
    eCommandReg         = 0x0012, // - command from controller
    eFirstCreditReg     = 0x0017,
    eLastCreditReg      = 0x0018  //- credit
};

// commands from controller. The same for terminal
namespace Command {
    const int BPOS_CmdNoCommand      = 0x00;
    const int BPOS_CmdPurchase       = 0x01;
    const int BPOS_CmdCancelWaitting = 0x02;
    const int BPOS_CmdCancel         = 0x03;
    const int BPOS_CmdConfirm        = 0x04;
    const int BPOS_CmdSettlement     = 0x05;
}

namespace Status {
    const int BPOS_StatusNoStatus                  = 0x00;
    const int BPOS_StatusWaittingCard              = 0x01;
    const int BPOS_StatusPaidSuccessfuly           = 0x02;
    const int BPOS_StatusPaymentCanceledByBank     = 0x03;
    const int BPOS_StatusPaymentCanceledByTerminal = 0x04;
    const int BPOS_StatusCardRead                  = 0x05;
}

namespace BPosStatusCodes {
    const int not_available                     = 0;
    const int card_was_read                     = 1;
    const int used_chip_card                    = 2;
    const int authorization_in_progress         = 3;
    const int waiting_for_cashier_action        = 4;
    const int printing_receipt                  = 5;
    const int pin_entry_is_needed               = 6;
    const int card_was_removed                  = 7;
    const int EMV_multi_aid                     = 8;
    const int waiting_for_card                  = 9;
    const int in_progress                       = 10;
    const int correct_transaction               = 11;
    const int pin_input_wait_key                = 12;
    const int pin_input_backspace_pressed       = 13;
    const int pin_input_key_pressed             = 14;

}

#endif // CONSTANTS_H
