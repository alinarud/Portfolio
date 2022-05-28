#ifndef BPOSCLIENT_H_
#define BPOSCLIENT_H_

//				RETURN CODES
#define ECRC_OK		 					0
#define ECRC_FAIL	 					1
#define ECRC_FAILEDTOOPENPORT			2
#define ECRC_FAILEDTOENUMETAREPORTS		3
#define ECRC_FAILEDTOCONNECT			4
#define ECRC_NOTOPENED					5
#define ECRC_NOTINITED					6
#define ECRC_BUSY						7
#define ECRC_NODATA						8
#define ECRC_MESSAGECORRUPTED			9
#define ECRC_TOOSMALLBUFFER				10
#define ECRC_DISCONNECTED				11
#define ECRC_RECVTIMEOUT				12
#define ECRC_SENDMESSAGE				13
#define ECRC_CONNECTION					14
#define ECRC_READ_FILE					15
#define ECRC_UNKNOWNERROR				16
#define ECRC_CHECKTERM_TO			    17

#define ECRC_SUCCESS(c)			(((int)(c)) == 0)
#define ECRC_FAILED(c)			(((int)(c)) != 0)

class CBPOSClient
{

public:
	CBPOSClient(){}
    virtual ~CBPOSClient() {}

	virtual int CommOpen(const char* sPort, unsigned int nBaudRate) = 0;
	virtual int CommOpenTCP(const char* sIP, const char* sPort) = 0;
	virtual int CommOpenAuto(unsigned int nBaudRate) = 0;
	virtual int CommClose() = 0;

	virtual int Confirm() = 0;
	virtual int Cancel() = 0;

	virtual int Purchase(unsigned int ulAmount, unsigned int ulAddAmount, unsigned char bMerchIdx) = 0;
	virtual int Refund(unsigned int ulAmount, unsigned int ulAddAmount, unsigned char bMerchIdx, char* bsRRN) = 0;
	virtual int Void(unsigned int ulInvoiceNum, unsigned char bMerchIdx) = 0;
	virtual int Settlement(unsigned char bMerchIdx) = 0;
	virtual int PrintBatchTotals(unsigned char bMerchIdx) = 0;

	virtual int PurchaseService(unsigned char bMerchIdx, unsigned int ulAmount, char* bsServiceParams) = 0;
	virtual int SetErrorLang(unsigned char bErrorLanguage) = 0;
	virtual int IdentifyCard(unsigned char bMerchIdx, char* bsCurrCode, unsigned char bAccNumber) = 0;

	virtual int get_LastResult(unsigned char& nVal) = 0;
	virtual int get_LastErrorCode(unsigned char& nVal) = 0;
	virtual int get_ResponseCode(unsigned int& nVal) = 0;
	virtual int get_DateTime(char* sVal, int nMaxSize) = 0;
	virtual int get_RRN(char* sVal, int nMaxSize) = 0;
	virtual int get_TxnType(unsigned char& nVal) = 0;
	virtual int get_TerminalID(char* sVal, int nMaxSize) = 0;
	virtual int get_MerchantID(char* sVal, int nMaxSize) = 0;
	virtual int get_AuthCode(char* sVal, int nMaxSize) = 0;

	virtual int get_LastErrorDescription(char* sVal, int nMaxSize) = 0;
	virtual int get_LastStatMsgCode(unsigned char& nVal) = 0;
	virtual int get_LastStatMsgDescription(char* sVal, int nMaxSize) = 0;

	virtual int get_PAN(char* sVal, int nMaxSize) = 0;

	virtual int get_ExpDate(char* sVal, int nMaxSize) = 0;
	virtual int get_CardHolder(char* sVal, int nMaxSize) = 0;
	virtual int get_IssuerName(char* sVal, int nMaxSize) = 0;
	virtual int get_InvoiceNum(unsigned int& nVal) = 0;
	virtual int get_CompletionInvoiceNum(unsigned int& nVal) = 0;

	virtual int get_TotalsDebitAmt(unsigned int& nVal) = 0;
	virtual int get_TotalsDebitNum(unsigned int& nVal) = 0;
	virtual int get_TotalsCreditAmt(unsigned int& nVal) = 0;
	virtual int get_TotalsCreditNum(unsigned int& nVal) = 0;
	virtual int get_TotalsCancelledAmt(unsigned int& nVal) = 0;
	virtual int get_TotalsCancelledNum(unsigned int& nVal) = 0;

	virtual int get_SignVerif(unsigned char& nVal) = 0;
	virtual int get_Receipt(char* sVal, int nMaxSize) = 0;
	virtual int get_emvAID(char* sVal, int nMaxSize) = 0;
	virtual int get_EntryMode(unsigned char& nVal) = 0;
	virtual int get_TxnNum(unsigned int& nVal) = 0;
	virtual int get_Amount(unsigned int& nVal) = 0;
	virtual int get_AddAmount(unsigned int& nVal) = 0;

	virtual int get_TermStatus(unsigned char& nVal) = 0;
	virtual int get_Key(unsigned char& nVal) = 0;
	virtual int get_Track3(char* sVal, int nMaxSize) = 0;
	virtual int get_TrnStatus(unsigned char& nVal) = 0;
	virtual int get_Currency(char* sVal, int nMaxSize) = 0;
	virtual int get_TrnBatchNum(unsigned int& nVal) = 0;
	virtual int get_RNK(char* sVal, int nMaxSize) = 0;
	virtual int get_CurrencyCode(char* sVal, int nMaxSize) = 0;
	virtual int get_AddData(char* sVal, int nMaxSize) = 0;
	virtual int get_TeminalInfo(char* sVal, int nMaxSize) = 0;
	virtual int get_DiscountName(char* sVal, int nMaxSize) = 0;
	virtual int get_DiscountAttribute(unsigned int& nVal) = 0;
	virtual int get_ECRDataTM(char* sVal, int nMaxSize) = 0;
	virtual int get_LibraryVersion(char* sVal, int nMaxSize) = 0;
	virtual int get_ScenarioData(char* sVal, int nMaxSize) = 0;

	virtual int GetTxnNum() = 0;
	virtual int GetTxnDataByOrder(unsigned int ulOrderNum) = 0;
	virtual int GetTxnDataByInv(unsigned int ulInvoiceNum, unsigned char bMerchIdx) = 0;
	virtual int GetBatchTotals(unsigned char bMerchIdx) = 0;
	virtual int CheckConnection(unsigned char bMerchIdx) = 0;
	virtual int ReqCurrReceipt() = 0;
	virtual int PrintLastSettleCopy(unsigned char bMerchIdx) = 0;
	virtual int PrintBatchJournal(unsigned char bMerchIdx) = 0;
	virtual int ReqReceiptByInv(unsigned int ulInvoiceNum, unsigned char bMerchIdx) = 0;

	virtual int SetControlMode(bool isCtrlMode) = 0;
	virtual int ReadKey(const unsigned char bTimeOut) = 0;
	virtual int DisplayText(const unsigned char bBeep) = 0;
	virtual int SetLine(const unsigned char bRow, const unsigned char bCol, const char* bsText, const unsigned char bInvert) = 0;
	virtual int ExchangeStatuses(const unsigned char bECRStatus) = 0;
	virtual int Completion(const unsigned char bMerchIdx, const unsigned int ulAmount, const char* bsRRN, const unsigned int ulInvoiceNum) = 0;
	virtual int ReadCard(void) = 0;
	virtual int Balance(const unsigned char bMerchIdx, const char* bsCurrCode, const unsigned char bAccNumber) = 0;
	virtual int Deposit(const unsigned char bMerchIdx, const unsigned int ulAmount, const char* bsCurrCode, const unsigned char bAccNumber) = 0;
	virtual int POSGetInfo(void) = 0;
	virtual int POSExTransaction(void) = 0;
	virtual int SelectApp(const char* bsAppName, const unsigned int ulAppIdx) = 0;
	virtual int CloseApp(void) = 0;
	virtual int StartScenario(const unsigned int ulScenarioID, const char* bsScenarioData) = 0;
	virtual int SetExtraPrintData(const char* bsExtraPrintData) = 0;
	virtual int SetExtraXmlData(const char* bsExtraXmlData) = 0;
	virtual int useLogging(const unsigned char bLoggingLevel, const char* bsFilePath) = 0;
	virtual int SendFile(const char* bsFullPath, const unsigned char bECRDataType, const unsigned char bECRCommand) = 0;
	virtual int SetScreen(const unsigned int ulScreenNumber) = 0;
	virtual int CorrectTransaction(const unsigned int ulAmount, const unsigned int ulAddAmount) = 0;

	virtual int CashAdvance(const unsigned char bMerchIdx, const unsigned int ulAmount, const char* sCurrCode, const unsigned char bAccNumber) = 0;
	virtual int ReadBankCard(void) = 0;
	virtual int get_FlagAcquirer(unsigned int &nVal) = 0;
	virtual int get_CryptedData(char* sVal, int nMaxSize) = 0;
	virtual int get_ExtraCardData(char* sVal, int nMaxSize) = 0;
	virtual int Ping(void) = 0;
	virtual int CheckTerminal(void) = 0;
	virtual int ReqDataFile(void) = 0;	
	virtual int get_DataFile(char* sVal, int nMaxSize) = 0;
	virtual int get_PanHash(char* sVal, int nMaxSize) = 0;
	virtual int get_SlipPrinted(unsigned char &nVal) = 0;
	virtual int get_TerminalInfo(char* sVal, int nMaxSize) = 0;
};

// Class factory "C" functions

typedef CBPOSClient* create_t();
typedef void destroy_t(CBPOSClient*);

#endif // BPOSCLIENT_H_
