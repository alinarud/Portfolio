/*
 * BPOSLibTest.h
 *
 *  Created on: Sep 17, 2014
 *      Author: maksym
 */

#ifndef BPOSLIBTEST_H_
#define BPOSLIBTEST_H_

#include <stdexcept>
#include <iostream>

#include "Config.h"
#include "BPOSClient.h"

static const char* gBPOSLibTestError[] = {
		"RRN is to long",
		"System error"
};

enum
{
	DATA_SIZE_MAX	= 4096,
	ERROR_SIZE_MAX	= 128,
	RRN_SIZE		= 12+1
};

std::istream& operator>> (std::istream& in, Scenarios& s)
{
	int val;
	if (in >> val)
	{
		switch ( val )
		{
			case Purchase: case Settlement: case PrintBatchTotals:
			case Confirm: case Get_Receipt: case Get_Receipt_ByInv:
			case Refund: case Void: case Cancel:
			case GetTxnNum: case GetTxnDataByOrder: case GetTxnDataByInv:
			case GetBatchTotals: case CheckConnection:
			case PrintLastSettleCopy: case PrintBatchJournal:
			case PurchaseService: case IdentifyCard:
			case SetErrorLang: case SetControlMode:
			case ReadKey: case DisplayText: case SetLine:
			case ExchangeStatuses: case Completion: case ReadCard:
			case Balance: case Deposit: case POSGetInfo:
			case POSExTransaction: case useSelectApp: case StartScenario:
			case SetExtraPrintData: case SetExtraXmlData: case useLogging:
			case SendFile: case SetScreen:
			s = Scenarios(val); break;

			default:
				throw std::out_of_range ( "Invalid value for type Scenarios" );
		}
	}
	return in;
}

std::ostream& operator<< (std::ostream& out, const Scenarios& s)
{
	switch (s)
	{
		case Purchase: 				out << "1";break;
		case Settlement: 			out << "2";break;
		case PrintBatchTotals: 		out << "3";break;
		case Confirm: 				out << "4";break;
		case Get_Receipt:			out << "5";break;
		case Get_Receipt_ByInv: 	out << "6";break;
		case Refund:				out << "7";break;
		case Void:					out << "8";break;
		case Cancel:				out << "9";break;
		case GetTxnNum:				out << "10";break;
		case GetTxnDataByOrder: 	out << "11";break;
		case GetTxnDataByInv: 		out << "12";break;
		case GetBatchTotals:		out << "13";break;
		case CheckConnection:		out << "14";break;
		case PrintLastSettleCopy:	out << "15";break;
		case PrintBatchJournal:		out << "16";break;
		case PurchaseService:		out << "17";break;
		case IdentifyCard:			out << "18";break;
		case SetErrorLang:			out << "19";break;
		case SetControlMode:		out << "20";break;
		case ReadKey:				out << "21";break;
//		case DisplayText:			out << "22";break;
//		case SetLine:				out << "23";break;
//		case ExchangeStatuses:		out << "24";break;
		case Completion:			out << "25";break;
		case ReadCard:				out << "26";break;
		case Balance:				out << "27";break;
		case Deposit:				out << "28";break;
		case POSGetInfo:			out << "29";break;
		case POSExTransaction:		out << "30";break;
//		case useSelectApp:			out << "31";break;
//		case StartScenario:			out << "32";break;
		case SetExtraPrintData:		out << "33";break;
		case SetExtraXmlData:		out << "34";break;
		case useLogging:			out << "35";break;
//		case SendFile:				out << "36";break;
//		case SetScreen:				out << "37";break;

	}

	return out;
}

void PritFunctList()
{
	std::cout << "____________________________________________________" << std::endl;
	std::cout << "Test Scenarios:"  << std::endl;
	std::cout << Purchase 		 	<< ": Purchase" << std::endl;
	std::cout << Settlement 		<< ": Settlement" << std::endl;
	std::cout << PrintBatchTotals 	<< ": PrintBatchTotals" << std::endl;
	std::cout << Confirm 		 	<< ": Confirm" << std::endl;
	std::cout << Get_Receipt 	 	<< ": Get_Receipt" << std::endl;
	std::cout << Get_Receipt_ByInv	<< ": Get_Receipt_ByInv" << std::endl;
	std::cout << Refund 		 	<< ": Refund" << std::endl;
	std::cout << Void 				<< ": Void" << std::endl;
	std::cout << Cancel			 	<< ": Cancel" << std::endl;
	std::cout << GetTxnNum			<< ": GetTxnNum" << std::endl;
	std::cout << GetTxnDataByOrder	<< ": GetTxnDataByOrder" << std::endl;
	std::cout << GetTxnDataByInv	<< ": GetTxnDataByInv" << std::endl;
	std::cout << GetBatchTotals		<< ": GetBatchTotals" << std::endl;
	std::cout << CheckConnection	<< ": CheckConnection" << std::endl;
	std::cout << PrintLastSettleCopy<< ": PrintLastSettleCopy" << std::endl;
	std::cout << PrintBatchJournal	<< ": PrintBatchJournal" << std::endl;
	std::cout << PurchaseService	<< ": PurchaseService" << std::endl;
	std::cout << IdentifyCard		<< ": IdentifyCard" << std::endl;
	std::cout << SetErrorLang		<< ": SetErrorLang" << std::endl;
	std::cout << SetControlMode		<< ": SetControlMode" << std::endl;
	std::cout << ReadKey			<< ": ReadKey" << std::endl;
//	std::cout << DisplayText		<< ": DisplayText" << std::endl;
//	std::cout << SetLine			<< ": SetLine" << std::endl;
//	std::cout << ExchangeStatuses	<< ": ExchangeStatuses" << std::endl;
	std::cout << Completion			<< ": Completion" << std::endl;
	std::cout << ReadCard			<< ": ReadCard" << std::endl;
	std::cout << Balance			<< ": Balance" << std::endl;
	std::cout << Deposit			<< ": Deposit" << std::endl;
	std::cout << POSGetInfo			<< ": POSGetInfo" << std::endl;
	std::cout << POSExTransaction	<< ": POSExTransaction" << std::endl;
//	std::cout << useSelectApp		<< ": useSelectApp" << std::endl;
//	std::cout << StartScenario		<< ": StartScenario" << std::endl;
	std::cout << SetExtraPrintData	<< ": SetExtraPrintData" << std::endl;
	std::cout << SetExtraXmlData	<< ": SetExtraXmlData" << std::endl;
	std::cout << useLogging			<< ": useLogging" << std::endl;
//	std::cout << SendFile			<< ": SendFile" << std::endl;
//	std::cout << SetScreen			<< ": SetScreen" << std::endl;
}

class BPosLib {
    BPosLib();
    ~BPosLib();

    void sendCommand(Params parameters);

private:
    void init();

private:
    void* lib;

};


#endif /* BPOSLIBTEST_H_ */
