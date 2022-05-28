/*
 * Config.h
 *
 *  Created on: Apr 12, 2016
 *      Author: maksym
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#include <string>

enum ParamNum
{
	CommOpt,
	Ip,
	Port,
	Com,
	BaudRate,
	Merch,
	Amount,
	RRN,
	TrnType,
	InvoiceNum,
	ErrorLang,
	AutoConfirm,
	None
};


typedef enum tagScenarios
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
    SetScreen,
//	CorrectionTransaction
} u;


struct Params
{
	unsigned int nCommOpt = 0;
	std::string sIP;
	std::string sPort;
	std::string sRRN;
    unsigned int u = Purchase;
	unsigned int nBaudRate = 0;
	unsigned int nAmount = 0;
	unsigned int nInvoiceNum = 0;
	unsigned char bMerchIdx = 0;
	unsigned char bErrorLang = 0;
	bool bIsAutoConfirm = false;
	bool bIsConsoleOn = false;
};



#endif /* CONFIG_H_ */
