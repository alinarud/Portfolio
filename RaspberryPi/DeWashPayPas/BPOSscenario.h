/*
 * BPOSscenario.h
 *
 *  Created on: Sep 17, 2014
 *      Author: maksym
 */

#ifndef BPOSSCENARIO_H_
#define BPOSSCENARIO_H_
#include "BPOSLibTest.h"
#include "BPOSwait.h"
#include "BPOSClient.h"
#include "Config.h"
#include <stdlib.h>
#include <memory>
#include <constants.h>

int RunScnario(Scenarios scenario, CBPOSClient *pBPOSClient, Params& parameters, std::time_t &start_time)
{
	using namespace std;
	int rc = ECRC_OK;
	char sError[128] 			= {0};
	unsigned char ucErrorCode 	= ECRC_OK;
	int Amount 				 	= parameters.nAmount;
	int addAmount			 	= 0;
	int MerchIdx 		    	= parameters.bMerchIdx;
	unsigned int ulInvoiceNum 	= parameters.nInvoiceNum;
	unsigned int ulOrderNum		= 0;
	char sRRN[DATA_SIZE_MAX] 	= {0};
	char sCurrCode[3+1]			={0};
	unsigned char bAccNumber 	= 0;
	std::string sData;

	if (parameters.sRRN.length() < RRN_SIZE)
		strcpy(sRRN, parameters.sRRN.c_str());
	else
		return -1; // should be error handling here

	switch(scenario)
	{
		case Purchase:
		{
			if (parameters.bIsConsoleOn)
			{
				cout << "Amount				= ";
				cin >> Amount;
				cout << "Additional amount 	= ";
				cin >> addAmount;
				cout << "Merchant Id		= ";
				cin >> MerchIdx;
			}
				rc = pBPOSClient->Purchase(Amount, addAmount, (unsigned char)MerchIdx);
			break;
		}
		case Settlement:
		{
			if (parameters.bIsConsoleOn)
			{
				cout << "MerchID:";
				cin >> MerchIdx;
			}
			rc = pBPOSClient->Settlement((unsigned char)MerchIdx);
			break;
		}
		case PrintBatchTotals:
		{
			if (parameters.bIsConsoleOn)
			{
				cout << "MerchID:";
				cin >> MerchIdx;
			}
			rc = pBPOSClient->PrintBatchTotals((unsigned char)MerchIdx);
			break;
		}
		case Confirm:
		{
			rc = pBPOSClient->Confirm();
			break;
		}
		case Get_Receipt:
		{
			cout << "=== Receipt ===" << endl;
			cout << "\tReqCurrReceipt = ";
			rc = pBPOSClient->ReqCurrReceipt();
			break;
		}
		case Get_Receipt_ByInv:
		{
			cout << "=== Receipt ===" << endl;
			cout << "\tReqReceiptByInv" <<endl;
			if (parameters.bIsConsoleOn)
			{
				cout << "\tulInvoiceNum	= ";
				cin >> ulInvoiceNum;
				cout << "\tMerchant Id	= ";
				cin >> MerchIdx;
			}
			rc = pBPOSClient->ReqReceiptByInv(ulInvoiceNum, (unsigned char)MerchIdx);
			WaitResponse(pBPOSClient, 60 * 1000, start_time);
			rc = pBPOSClient->ReqCurrReceipt();
			break;
		}
		case Refund:
		{
			if (parameters.bIsConsoleOn)
			{
				cout << "Amount 		   	= ";
				cin >> Amount;
				cout << "Additional amount 	= ";
				cin >> addAmount;
				cout << "Merchant Id		= ";
				cin >> MerchIdx;
				cout << "RRN  	         	= ";
				cin >> sRRN;
			}
			if (strlen(sRRN) > RRN_SIZE)
			{
				rc = ECRC_FAIL;
				memcpy(sError, gBPOSLibTestError[0], sizeof(gBPOSLibTestError[0]));
			}
			else
				rc = pBPOSClient->Refund(Amount, addAmount, (unsigned char)MerchIdx, sRRN);
			break;
		}
		case Void:
		{
			if (parameters.bIsConsoleOn)
			{
				cout << "ulInvoiceNum 	 = ";
				cin >> ulInvoiceNum;
				cout << "Merchant Id     = ";
				cin >> MerchIdx;
			}

			rc = pBPOSClient->Void(ulInvoiceNum, (unsigned char)MerchIdx);
			break;
		}
		case Cancel:
		{
			rc = pBPOSClient->Cancel();
			cout << "After WaitTimeOut(): " << endl;
			pBPOSClient->get_LastErrorCode(ucErrorCode);
			cout << "Last ErrorCode: "<<  static_cast<int>(ucErrorCode) << endl;
			char sCP1251_err[ERROR_SIZE_MAX] 	= {0};
			iconv_t d;
			pBPOSClient->get_LastErrorDescription(sError, 128);
			d = iconv_open("UTF-8","CP1251");
			Utf(sError, sCP1251_err, d);
			cout << "Last Error: " << sCP1251_err << endl;
			iconv_close(d);
			break;
		}
		case GetTxnNum:
		{
			rc = pBPOSClient->GetTxnNum();
			break;
		}
		case GetTxnDataByOrder:
		{
			cout << "Order num 	 = ";
			cin >> ulOrderNum;
			rc = pBPOSClient->GetTxnDataByOrder(ulOrderNum);
			break;
		}
		case GetTxnDataByInv:
		{
			if (parameters.bIsConsoleOn)
			{
				cout << "ulInvoiceNum 	 = ";
				cin >> ulInvoiceNum;
				cout << "Merchant Id     = ";
				cin >> MerchIdx;
			}
			rc = pBPOSClient->GetTxnDataByInv(ulInvoiceNum, MerchIdx);
			break;
		}
		case GetBatchTotals:
		{
			if (parameters.bIsConsoleOn)
			{
				cout << "Merchant Id     = ";
				cin >> MerchIdx;
			}
			rc = pBPOSClient->GetBatchTotals(MerchIdx);
			break;
		}
		case CheckConnection:
		{
			if (parameters.bIsConsoleOn)
			{
				cout << "Merchant Id     = ";
				cin >> MerchIdx;
			}
			rc = pBPOSClient->CheckConnection(MerchIdx);
			break;
		}
		case PrintLastSettleCopy:
		{
			if (parameters.bIsConsoleOn)
			{
				cout << "Merchant Id     = ";
				cin >> MerchIdx;
			}
			rc = pBPOSClient->PrintLastSettleCopy(MerchIdx);
			break;
		}
		case PrintBatchJournal:
		{
			if (parameters.bIsConsoleOn)
			{
				cout << "Merchant Id     = ";
				cin >> MerchIdx;
			}
			rc = pBPOSClient->PrintBatchJournal(MerchIdx);
			break;
		}
		case PurchaseService:
		{
			cout << "Merchant Id    = ";
			cin >> MerchIdx;
//				char servicesParam[] = "0001//1//5";
			cout << "Amount			= ";
			cin >> Amount;
			char servicesParam[24] = {0};
			cout << "servicesParam	= ";
			cin >> servicesParam;
			rc = pBPOSClient->PurchaseService(MerchIdx, Amount, servicesParam);
			break;
		}
		case IdentifyCard:
		{
			cout << "Merchant Id     = ";
			cin >> MerchIdx;
			cout << "bsCurrCode      = ";
			cin >> sCurrCode;
			cout << "AccNumber	     = ";
			cin >> bAccNumber;
			rc = pBPOSClient->IdentifyCard(MerchIdx, sCurrCode, bAccNumber);
			break;
		}
		case SetErrorLang:
		{
			unsigned int uiLangNum = 0;
			cout << "Chose language (0-EN, 1-UA, 2-RU)" << endl;
			cin >> uiLangNum;
			switch(uiLangNum)
			{
			case 0:
				cout << "English" << endl;
				break;
			case 1:
				cout << "Ukrainian" << endl;
				break;
			case 2:
				cout << "Russian" << endl;
				break;
			default:
				cout << uiLangNum << ": variant is not present." << endl;
				cout << "English is chosen by default" << endl;
				uiLangNum = 0;
			}
			rc = pBPOSClient->SetErrorLang(uiLangNum);
			break;
		}
		case SetControlMode:
		{
			bool isCtrlMode = false;
			cout << "Control mode:\n 0. FALSE;\n 1. TRUE" << endl;
			cin >> isCtrlMode;
			rc = pBPOSClient->SetControlMode(isCtrlMode);
			break;
		}
		case ReadKey:
		{
			cout << "bTimeout		:" << endl;
			unsigned char bTimeOut = 0;
			cin >> bTimeOut;
			pBPOSClient->ReadKey(bTimeOut);
			break;
		}
		case DisplayText:
		{
			cout << "Currently is not implemented! "<< endl;
//			cin >> ;
//			pBPOSClient->;
			break;
		}
		case SetLine:
		{
			cout << "Currently is not implemented! "<< endl;
//			cin >> ;
//			pBPOSClient->;
			break;
		}
		case ExchangeStatuses:
		{
			cout << "Currently is not implemented! "<< endl;
//			cin >> ;
//			pBPOSClient->;
			break;
		}
		case Completion:
		{
			if (parameters.bIsConsoleOn)
			{
				cout << "Merchant Id		= ";
				cin >> MerchIdx;
				cout << "Amount 		   	= ";
				cin >> Amount;
				cout << "Invoice num 	= ";
				cin >> ulInvoiceNum;
				cout << "RRN  	         	= ";
				cin >> sRRN;
			}
			if (strlen(sRRN) > RRN_SIZE)
			{
				rc = ECRC_FAIL;
				memcpy(sError, gBPOSLibTestError[0], sizeof(gBPOSLibTestError[0]));
			}
			else
				rc = pBPOSClient->Completion(MerchIdx, Amount, sRRN, ulInvoiceNum);

			break;
		}
		case ReadCard:
		{
			cout << "ReadCard()"<< endl;
//			cin >> ;
			pBPOSClient->ReadCard();
			break;
		}
		case Balance:
		{
			cout << "Balance()"<< endl;
			cout << "Merchant Id     = ";
			cin >> MerchIdx;
			cout << "bsCurrCode      = ";
			cin >> sCurrCode;
			cout << "AccNumber	     = ";
			cin >> bAccNumber;
			rc = pBPOSClient->Balance(MerchIdx, sCurrCode, bAccNumber);
			break;
		}
		case Deposit:
		{
			cout << "Deposit()"<< endl;
			cout << "Merchant Id     = ";
			cin >> MerchIdx;
			cout << "Amount 		 = ";
			cin >> Amount;
			cout << "bsCurrCode      = ";
			cin >> sCurrCode;
			cout << "AccNumber	     = ";
			cin >> bAccNumber;
			rc = pBPOSClient->Deposit(MerchIdx, Amount, sCurrCode, bAccNumber);
			break;
		}
		case POSGetInfo:
		{
			cout << "POSGetInfo() "<< endl;
//			cin >> ;
			rc = pBPOSClient->POSGetInfo();
			break;
		}
		case POSExTransaction:
		{
			cout << "POSExTransaction() "<< endl;
//			cin >> ;
			rc = pBPOSClient->POSExTransaction();
			break;
		}
		case useSelectApp:
		{
			cout << "Currently is not implemented! "<< endl;
//			cin >> ;
//			pBPOSClient->;
			break;
		}
		case StartScenario:
		{
			cout << "Currently is not implemented! "<< endl;
//			cin >> ;
//			pBPOSClient->;
			break;
		}
		case SetExtraPrintData:
		{
			cout << "SetExtraPrintData: "<< endl;
			cin >> sData;;
			rc = pBPOSClient->SetExtraPrintData(sData.c_str());
			break;
		}
		case SetExtraXmlData:
		{
			cout << "SetExtraXmlData: "<< endl;
			cin >> sData;
			rc = pBPOSClient->SetExtraXmlData(sData.c_str());
			break;
		}
		case useLogging:
		{
			cout << "useLogging()"<< endl;
			unsigned char bLoggingLevel = 0;
			std::string sPath;
			cout << "Enter logging level:		";
			cin >> bLoggingLevel;
			cout << "Enter path to log file:	" << endl;
			cin >> sPath;
			pBPOSClient->useLogging(bLoggingLevel, sPath.c_str());
			break;
		}
		case SendFile:
		{
			cout << "Currently is not implemented! "<< endl;
//			cin >> ;
//			pBPOSClient->;
			break;
		}
		case SetScreen:
		{
			cout << "Currently is not implemented! "<< endl;
//			cin >> ;
//			pBPOSClient->;
			break;
		}
		default:
		   rc = pBPOSClient->Purchase(500, 0, 1);
		   break;
	}
	return rc;
}

int FinishScenario(Scenarios scenarion, CBPOSClient *pBPOSClient, Params parameters, std::time_t &start_time)
{
	using namespace std;
	int rc = 0;
	char sStrVal[DATA_SIZE_MAX] = {0};
	char sError[ERROR_SIZE_MAX] = {0};
	unsigned int nNumVal 	= 0;
	unsigned char ucVal 	= 0;
	if (scenarion == Confirm)
	{
		char sCP1251[DATA_SIZE_MAX] 	= {0};
		iconv_t d;

		rc = pBPOSClient->ReqCurrReceipt();
		WaitResponse(pBPOSClient, 60 * 1000, start_time);

		cout << "\tReceipt = " << endl;
		rc = pBPOSClient->get_Receipt(sCP1251, DATA_SIZE_MAX);
		// convert from CP1251 to UTF-8
		d = iconv_open("UTF-8","CP1251");
		Utf(sCP1251, sStrVal, d);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;
		iconv_close(d);
	}
	else if ((Get_Receipt == scenarion) || (Get_Receipt_ByInv == scenarion))
	{
		char sCP1251[DATA_SIZE_MAX] 	= {0};
		wchar_t wbuff[DATA_SIZE_MAX] 	= {0};
		iconv_t d;

		cout << "\tReceipt = " << endl;
		rc = pBPOSClient->get_Receipt(sCP1251, DATA_SIZE_MAX);
		// convert from CP1251 to UTF-8
		d = iconv_open("UTF-8","CP1251");
		Utf(sCP1251, sStrVal, d);
		if(ECRC_SUCCESS(rc))
		{
			cout << sStrVal << endl;
		}
		else
			cout << "No Data" << endl;
		iconv_close(d);
		// convert from myltibyte to wide char
		setlocale(LC_CTYPE, "");
		int len = mbstowcs(NULL, sStrVal, 0);
		mbstowcs(wbuff, sStrVal, len);

	}
	else
	{
		cout << "==== Transaction info ====" << endl;
		unsigned int nRespCode = 0;
		cout << "\tResponseCode = ";
		rc = pBPOSClient->get_ResponseCode(nRespCode);
		if(ECRC_SUCCESS(rc))
			cout << nRespCode << endl;
		else
			cout << "No Data" << endl;

		cout << "\tExp. Date = ";
		rc = pBPOSClient->get_ExpDate(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tDateTime = ";
		rc = pBPOSClient->get_DateTime(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tAuthCode = ";
		rc = pBPOSClient->get_AuthCode(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tTerminalID = ";
		rc = pBPOSClient->get_TerminalID(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tMerchantID = ";
		rc = pBPOSClient->get_MerchantID(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tget_TxnNum = ";
		rc = pBPOSClient->get_TxnNum(nNumVal);
		if(ECRC_SUCCESS(rc))
			cout << nNumVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tget_CardHolder = ";
		rc = pBPOSClient->get_CardHolder(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tTotalsDebitAmt = ";
		rc = pBPOSClient->get_TotalsDebitAmt(nNumVal);
		if(ECRC_SUCCESS(rc))
			cout << nNumVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tTotalsDebitNum = ";
		rc = pBPOSClient->get_TotalsDebitNum(nNumVal);
		if(ECRC_SUCCESS(rc))
			cout << nNumVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tTotalsCreditAmt = ";
		rc = pBPOSClient->get_TotalsCreditAmt(nNumVal);
		if(ECRC_SUCCESS(rc))
			cout << nNumVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tget_TotalsCreditNum = ";
		rc = pBPOSClient->get_TotalsCreditNum(nNumVal);
		if(ECRC_SUCCESS(rc))
			cout << nNumVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tTotalsCancelledAmt = ";
		rc = pBPOSClient->get_TotalsCancelledAmt(nNumVal);
		if(ECRC_SUCCESS(rc))
			cout << nNumVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tget_TotalsCancelledNum = ";
		rc = pBPOSClient->get_TotalsCancelledNum(nNumVal);
		if(ECRC_SUCCESS(rc))
			cout << nNumVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tget_IssuerName = ";
		rc = pBPOSClient->get_IssuerName(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tInvoiceNum = ";
		rc = pBPOSClient->get_InvoiceNum(nNumVal);
		if(ECRC_SUCCESS(rc))
			cout << nNumVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tTxnType = ";
		rc = pBPOSClient->get_TxnType(ucVal);
		if(ECRC_SUCCESS(rc))
			cout << static_cast<int>(ucVal) << endl;
		else
			cout << "No Data" << endl;

		cout << "\tLastStatMsgCode = ";
		rc = pBPOSClient->get_LastStatMsgCode(ucVal);
		if(ECRC_SUCCESS(rc))
			cout << static_cast<int>(ucVal) << endl;
		else
			cout << "No Data" << endl;

		cout << "\tLastStatMsgDescription = ";
		rc = pBPOSClient->get_LastStatMsgDescription(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tPAN = ";
		rc = pBPOSClient->get_PAN(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tSignVerif = ";
		rc = pBPOSClient->get_SignVerif(ucVal);
		if(ECRC_SUCCESS(rc)){
			if (ucVal == 0)
				cout << "Sign is not needed"<< endl;
			else if (ucVal == 1)
				cout << "Sign is needed"<< endl;
		}
		else
			cout << "No Data" << endl;

		cout << "\temvAID = ";
		rc = pBPOSClient->get_emvAID(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tEntryMode = ";
		rc = pBPOSClient->get_EntryMode(ucVal);
		if(ECRC_SUCCESS(rc))
		{
			switch(static_cast<int>(ucVal))
			{
			case 0: cout << "undefined" << endl; break;
			case 1: cout << "Magnetic stripe card" << endl; break;
			case 2: cout << "EMV chip card" << endl; break;
			case 3: cout << "Contactless chip card" << endl; break;
			case 4: cout << "Contactless stripe card" << endl; break;
			case 5: cout << "Fallback (magnetic stripe was used by card that has EMV chip)" << endl; break;
			case 6: cout << "Manual (card number was entered manually)" << endl; break;
			}
		}
		else
			cout << "No Data" << endl;

		cout << "\tAmount = ";
		rc = pBPOSClient->get_Amount(nNumVal);
		if(ECRC_SUCCESS(rc))
			cout << nNumVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tAddAmount = ";
		rc = pBPOSClient->get_AddAmount(nNumVal);
		if(ECRC_SUCCESS(rc))
			cout << nNumVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tRRN = ";
		rc = pBPOSClient->get_RRN(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tTermStatus = ";
		rc = pBPOSClient->get_TermStatus(ucVal);
		if(ECRC_SUCCESS(rc))
			cout << static_cast<int>(ucVal) << endl;
		else
			cout << "No Data" << endl;

		cout << "\tget_Key = ";
		rc = pBPOSClient->get_Key(ucVal);
		if(ECRC_SUCCESS(rc))
			cout << static_cast<int>(ucVal) << endl;
		else
			cout << "No Data" << endl;

		cout << "\tTrack3 = ";
		rc = pBPOSClient->get_Track3(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tget_TrnStatus = ";
		rc = pBPOSClient->get_TrnStatus(ucVal);
		if(ECRC_SUCCESS(rc))
			cout << static_cast<int>(ucVal) << endl;
		else
			cout << "No Data" << endl;

		cout << "\tCurrency = ";
		rc = pBPOSClient->get_Currency(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tTrnBatchNum = ";
		rc = pBPOSClient->get_TrnBatchNum(nNumVal);
		if(ECRC_SUCCESS(rc))
			cout << nNumVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tRNK = ";
		rc = pBPOSClient->get_RNK(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;
		cout << "\tCurrencyCode = ";
		rc = pBPOSClient->get_CurrencyCode(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;
		cout << "\tAddData = ";
		rc = pBPOSClient->get_AddData(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;
		cout << "\tTerminalInfo = ";
		rc = pBPOSClient->get_TeminalInfo(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;
		cout << "\tDiscountName = ";
		rc = pBPOSClient->get_DiscountName(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tDiscountAttribute = ";
		rc = pBPOSClient->get_DiscountAttribute(nNumVal);
		if(ECRC_SUCCESS(rc))
			cout << nNumVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tECRDataTM = ";
		rc = pBPOSClient->get_ECRDataTM(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tLibraryVersion = ";
		rc = pBPOSClient->get_LibraryVersion(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		cout << "\tScenarioData = ";
		rc = pBPOSClient->get_ScenarioData(sStrVal, 128);
		if(ECRC_SUCCESS(rc))
			cout << sStrVal << endl;
		else
			cout << "No Data" << endl;

		char sCP1251_err[ERROR_SIZE_MAX] 	= {0};
		iconv_t d;
		pBPOSClient->get_LastErrorDescription(sError, 128);
		d = iconv_open("UTF-8","CP1251");
		Utf(sError, sCP1251_err, d);
		cout << "Last Error: " << sCP1251_err << endl;
		iconv_close(d);
	}
}

#endif /* BPOSSCENARIO_H_ */
