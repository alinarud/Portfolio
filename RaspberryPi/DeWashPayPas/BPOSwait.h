/*
 * BPOSwait.h
 *
 *  Created on: Sep 17, 2014
 *      Author: maksym
 */

#ifndef BPOSWAIT_H_
#define BPOSWAIT_H_

#include "BKCconvert.h"
#include "BPOSClient.h"
#include <ctime>

bool WaitResponse(CBPOSClient* plBPOSClient, unsigned long timeout, std::time_t &start_time)
{
	using namespace std;
	cout << " WaitResponse() | timeout: " << timeout << endl;
	int rc = 0;
	char strVal[128];
	char strLastStatMsgDescr[128] = {0};
	unsigned char ucVal = 0;
	static unsigned char ucLastStatusCode = 0;
	cout << "ucLastStatusCode" << (int)ucLastStatusCode << endl;
	unsigned long currTime = 0;
	timeout *= 1000;
	iconv_t d;
	d = iconv_open("UTF-8","CP1251");
	do
	{

		rc = plBPOSClient->get_LastStatMsgCode(ucVal);
		if (ucVal != ucLastStatusCode)
		{
			cout << "refreshing ping timeout" << endl;
			start_time = time(0);
		}
		if (ucVal && (ucLastStatusCode != ucVal))
		{
			ucLastStatusCode = ucVal;
			cout << "\tLastStatMsgCode = ";
			cout << static_cast<int>(ucVal) << endl;
			if (ucVal == 11)
			{
				cout << "Correction transaction received!" << endl;
				char sPAN[16+1] = {0};
				unsigned char ucEntryMode = 0;
				plBPOSClient->get_PAN(sPAN, 16);
				plBPOSClient->get_EntryMode(ucEntryMode);
				cout << "PAN:		" << sPAN << endl;
				cout << "EntryMode:	" << static_cast<int>(ucEntryMode) << endl;
				cout << "Do you need to correct transaction? (\"0\" - NO, \"1\" - YES)"<< endl;
				int res = 0;
				cin >> res;
				if (res == 1)
				{
					unsigned int Amount = 0;
					unsigned int AddAmount = 0;
					cout << "write correction transaction data" << endl;
					cout << "Amount		:";
					cin >> Amount;
					cout << "AddAmount	:";
					cin >> AddAmount;
					plBPOSClient->CorrectTransaction(Amount, AddAmount);
				}
			}
		}

		rc = plBPOSClient->get_LastStatMsgDescription(strVal, 128);
		if(ucVal && (strcmp(strLastStatMsgDescr, strVal)))
		{
			memcpy(strLastStatMsgDescr, strVal, sizeof(strVal));
			char sCP1251[ERROR_SIZE_MAX] 	= {0};
			Utf(strVal, sCP1251, d);
			cout << "\tLastStatMsgDescription = ";
			cout << sCP1251 << endl;
		}

		usleep(250 * 1000);
		currTime += 250 * 1000;

		unsigned char ucLastRes;
		plBPOSClient->get_LastResult(ucLastRes);
		if(ucLastRes != 2)
			break;
	}
	while(true && (timeout >= currTime));
	iconv_close(d);
	if (timeout <= currTime)
		return true;
	else
		return false;
}


#endif /* BPOSWAIT_H_ */
