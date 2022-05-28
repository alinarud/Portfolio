/*
 * Console.h
 *
 *  Created on: Apr 12, 2016
 *      Author: maksym
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_
#include <string>
#include <string.h>
#include <iostream>
#include "Config.h"

using namespace std;

struct Options
{
	std::string sName;
	bool 		bIsReeequired;
	bool		bIsValueNeeded;
	std::string sValue;
};

enum ErrorParse
{
	Ok,
	BadParam_Specificator,
	BadParam_Name,
	BadParam_Value
};

// name, required, isValueExists, value
static Options console_opt[] =
{
	{ "commopt", 		true,  true, string() },
	{ "ip", 			false, true, string() },
	{ "port", 			false, true, string() },
	{ "com", 			false, true, string() },
	{ "baudrate",		false, true, string() },
	{ "merch", 			false, true, string() },
	{ "amount", 		false, true, string() },
	{ "rrn", 			false, true, string() },
	{ "trntype", 		true,  true, string() },
	{ "invoicenum",		false, true, string() },
	{ "errorlang",		false, true, string() },
	{ "autoconfirm",	false, false },
};

int PrintHelp()
{
	cout << "-commopt :\t communication option type: 0 - CommOpen, 1 - CommOpenTCP, 2 - CommOpenAuto" << endl;
	cout << "-ip :\t\t terminal ip address" << endl;
	cout << "-port :\t\t terminal TCP or COM port" << endl;
	cout << "-baudrate :\t terminal baudrate" << endl;
	cout << "-merch :\t merchant index" << endl;
	cout << "-amount :\t " << endl;
	cout << "-rrn :\t" << endl;
	cout << "-trntype :\t transaction type: 1- Purchase, 2 - Settlement, 3 - PrintBatchTotals, 5 - Get_Receipt, 7 - Refund, 8 - Void " << endl;
	cout << "-invoicenum :\t" << endl;
	cout << "-errorlang :\t " << endl;
	cout << "-autoconfirm :\t set if autoconfirm is needed for input transaction type" << endl;

	return 0;
}

ErrorParse WriteError(ErrorParse code, std::string sText)
{
	switch (code)
	{
	case ErrorParse::BadParam_Specificator:
		cout << "Please, use \"-\" or \"\\\" as parameter name specificator" << endl;
		break;
	case ErrorParse::BadParam_Name:
		cout << "Please, enter valid parameter name" << endl;
		break;
	case ErrorParse::BadParam_Value:
		cout << "Please, enter valid parameter value" << endl;
		break;
	case ErrorParse::Ok:
	default:
		break;
	}
	cout << sText << endl;

	return code;
}

void u(Params &parameters, int index, std::string value = "")
{
	switch (index)
	{
	case CommOpt:
		parameters.nCommOpt = std::atoi(value.c_str());
		break;
	case Ip:
		parameters.sIP = value;
		break;
	case Port:
	case Com:
		parameters.sPort = value;
		break;
	case BaudRate:
		parameters.nBaudRate = std::atoi(value.c_str());
		break;
	case Merch:
		parameters.bMerchIdx = std::atoi(value.c_str());
		break;
	case Amount:
		parameters.nAmount = std::atoi(value.c_str());
		break;
	case RRN:
		parameters.sRRN = value;
		break;
	case TrnType:
		parameters.nTrnType = std::atoi(value.c_str());
		break;
	case InvoiceNum:
		parameters.nInvoiceNum = std::atoi(value.c_str());
		break;
	case ErrorLang:
		parameters.bErrorLang = *value.c_str();
		break;
	case AutoConfirm:
		parameters.bIsAutoConfirm = true;
		break;
	default:
		break;
	}
}

ErrorParse ParseParams(Params &parameters, int argc, char **argv)
{
	auto index = 0;
	while (index < argc)
	{
		if ((argv[index][0] != '-') && (argv[index][0] != '/'))
			return WriteError(ErrorParse::BadParam_Specificator, argv[index]);
		for (unsigned int i = 0; i < sizeof(console_opt) / sizeof(Options); i++)
		{
			if (strcmp(argv[index]+1, console_opt[i].sName.c_str()) == 0)
			{
				if (console_opt[i].bIsValueNeeded)
					if (index + 1 < argc) {
						SetParams(parameters, i, argv[index + 1]);
						index++; // skip parameter value
						break;
					}
					else
						return WriteError(ErrorParse::BadParam_Value, string("Empty value for parameter: ") + argv[index]);
				else
					SetParams(parameters, i);
			}
		}
		index++;
	}

	return ErrorParse::Ok;
}

#endif /* CONSOLE_H_ */
