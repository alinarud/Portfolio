//============================================================================
// Name        : BPOSLibTest.cpp
// Author      : Maksym Makarychev
// Version     :
// Copyright   : JSC Bancomzvjazok
// Description : Sample: How to use BPOSLib
//============================================================================
#include <string>
#include <string.h>
#include <iostream>
#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>
#include "BPOSscenario.h"
#include "Console.h"
#include "SerialPort.h"

using namespace std;


bool PrintInfo(int retCode, CBPOSClient* m_pBPOSClient)
{
    if (m_pBPOSClient == 0)
		return true;

	if(ECRC_FAILED(retCode))
	{
		unsigned char ucErrorCode = ECRC_OK;
        m_pBPOSClient->get_LastErrorCode(ucErrorCode);
		cout << "Last ErrorCode: "<<  static_cast<int>(ucErrorCode) << endl;

		char sError[ERROR_SIZE_MAX] 	= {0};
		char sCP1251_err[ERROR_SIZE_MAX] 	= {0};
		iconv_t d;
        m_pBPOSClient->get_LastErrorDescription(sError, 128);
		d = iconv_open("UTF-8","CP1251");
		Utf(sError, sCP1251_err, d);
		cout << "Last Error: " << sCP1251_err << endl;
		iconv_close(d);
		return true;
	}

	return false;
}

bool WaitResAndFinish(Scenarios &scenarion, CBPOSClient* m_pBPOSClient, Params &parameters)
{
	int countCycle = 0;
	unsigned char nLastRes;
	time_t start_time = time(0);
	do {
        bool bTimeOut = WaitResponse(m_pBPOSClient, 120 * 1000, start_time);
		long duration = (time(0) - start_time); //clock_per_sec
		if (duration >= 20)
		{
			cout << "CheckTerminal "<< endl;
            m_pBPOSClient->CheckTerminal();
			start_time = time(0);
		}
        m_pBPOSClient->get_LastResult(nLastRes);
		countCycle++;
	} while(nLastRes == 2);


    m_pBPOSClient->get_LastResult(nLastRes);
	cout << "Last result = " << static_cast<int>(nLastRes) << endl;
	if(nLastRes == 0)
	{
		cout << "== Transaction Success ==" << endl;
        FinishScenario(scenarion, m_pBPOSClient, parameters, start_time);
	}
	else if ((nLastRes == 1) && (Get_Receipt_ByInv == scenarion))
	{
		cout << "\tReceipt is not presented" << endl;
	}
	else
	{
		cout << "Transaction NOT Success:" << endl;
        PrintInfo(nLastRes, m_pBPOSClient);
		unsigned int nRC;
		cout << "\tResponseCode = ";
        int rc = m_pBPOSClient->get_ResponseCode(nRC);
		if(ECRC_SUCCESS(rc))
			cout << nRC << endl;
		else
			cout << "No Data" << endl;
	}
}
/*
int main(int argc, char **argv)
{
    // INIT SERIAL PORT (set connection with controller)
    SerialPort serialPort;

    printf("PORT");

    serialPort.closeSerialPort();


	Params parameters;
	if (argc == 1) // no input parameters
		parameters.bIsConsoleOn = true;
	else
	{
		if (strcmp(*(++argv) + 1, "help") == 0)
			return PrintHelp();

		ErrorParse rc = ParseParams(parameters, argc - 1, argv);
		if (rc != ErrorParse::Ok)
			return -1;
	}

    getchar();
    return 0;

*/
/*
	//load BPOSLib
	void* lib = dlopen("libBPOSLib.so", RTLD_LAZY);
	if(!lib)
	{
		cout << "Cannot load library: " << dlerror() << endl;
		return 0;
	}

	//reset errors
	dlerror();

	//load the symbols
	create_t* creatBPOSInstance = (create_t*) dlsym(lib, "create");
	const char* dlsym_error = dlerror();
	if(dlsym_error)
    {while(1)
    {

    }
		cout << "Cannot load symbol create: " << dlsym_error << endl;
		return 0;
	}

	destroy_t* destroyBPOSInstance = (destroy_t*) dlsym(lib, "destroy");
	dlsym_error = dlerror();
	if(dlsym_error)
	{
		cout << "Cannot load symbol destroy: " << dlsym_error << endl;
		return 0;
	}

	//create an instance of GTBClient
    CBPOSClient* m_pBPOSClient = creatBPOSInstance();

	if (parameters.bIsConsoleOn)
	{
		cout << "COM port configuration " << endl;
		cout << "0. CommOpen() " << endl;
		cout << "1. CommOpenTCP() " << endl;
		#ifdef _UDEV
			cout << "2. CommOpenAuto() " << endl;
		#endif
		cin >> parameters.nCommOpt;
		if (parameters.nCommOpt == 0)
		{
			cout << "Port name: ";
			cin >> parameters.sPort;
			cout << "Baud rate: ";
			cin >> parameters.nBaudRate;
		}else if (parameters.nCommOpt == 1)
		{
			cout << "IP: ";
			cin >> parameters.sIP;
			cout << "Port: ";
			cin >> parameters.sPort;
		}
		#ifdef _UDEV
			else if (parameters.nCommOpt == 2)
			{
				cout << "Baud rate: ";
				cin >> parameters.nBaudRate;
			}
		#endif
	}
	cout << "useLogging()..." << endl;
    m_pBPOSClient->useLogging(2, "logbpos.txt");
	cout << "SetErrorLang...." << endl;
    int rc = m_pBPOSClient->SetErrorLang(static_cast<int>(parameters.bErrorLang));
	cout << "SetErrorLang... OK" << endl;
	do
	{
        if(!m_pBPOSClient)
			break;
		if (parameters.bIsConsoleOn)
			PritFunctList();

		Scenarios scenarion = static_cast<Scenarios>(parameters.nTrnType);
		if (parameters.bIsConsoleOn)
		{
			cout << "Test with scenario (1/2/3/4/5/6/7/8/9/10/11/12/13/14/15/16/17/18/19/20/21/22/23/24/25/26/27/28/29/30/31/32/33/34/35/36/37/38)";
			try
			{
				cin >> scenarion;
			} catch ( out_of_range& ex )
			{
				cerr << ex.what() <<endl;
			}
		}
		cout << "CommClose... " << endl;
		char sError[128];
		unsigned char ucErrorCode = ECRC_OK;
        rc = m_pBPOSClient->CommClose();
		cout << "CommClose... OK" << endl;
		if (parameters.nCommOpt == 0){
			cout << "CommOpen..." << endl;
            rc = m_pBPOSClient->CommOpen(parameters.sPort.c_str(), parameters.nBaudRate);
			cout << "CommOpen... OK" << endl;
		}
		else if (parameters.nCommOpt == 1)
            rc = m_pBPOSClient->CommOpenTCP(parameters.sIP.c_str(), parameters.sPort.c_str());
		#ifdef _UDEV
		else
            rc = m_pBPOSClient->CommOpenAuto(parameters.nBaudRate);
		#endif

		cout << "get_LastResult()..." << endl;
		unsigned char ucLastResult = 0;
        m_pBPOSClient->get_LastResult(ucLastResult);
		cout << "LastResult = " <<  static_cast<int>(ucLastResult) << endl;
        if (PrintInfo(rc, m_pBPOSClient))
			break;

		time_t start_time = time(0);
        rc = RunScenario(scenarion, m_pBPOSClient, parameters, start_time);
        if (PrintInfo(rc, m_pBPOSClient))
			continue;

		switch (scenarion)
		{
		case SetExtraPrintData:
		case SetExtraXmlData:
		case useLogging:
			continue;
		}

        WaitResAndFinish(scenarion, m_pBPOSClient, parameters);

		if (parameters.bIsAutoConfirm)
		{
			cout << " === AUTOCONFIRM === " << endl;
            rc = RunScenario(Confirm, m_pBPOSClient, parameters, start_time);
            if (PrintInfo(rc, m_pBPOSClient))
				continue;

            WaitResAndFinish(scenarion, m_pBPOSClient, parameters);
		}
    }
	while(true && parameters.bIsConsoleOn);

	//destroy the instance of GTBClient
    destroyBPOSInstance(m_pBPOSClient);


	//unload the library
	serialPort.closeSerialPort();
    dlclose(lib);
    sleep(1);*/

//}


BPosLib::BPosLib()
{

}

BPosLib::~BPosLib()
{
    dlclose(lib);
}

void BPosLib::sendCommand(Params parameters)
{

    //create an instance of GTBClient

    /*
     *
IP=10.1.1.2
Port=2000
Merchant=1
Amount=100

./BPOSLibTest -commopt 1 -ip $IP -port $Port -merch $Merchant -amount $Amount -trntype 1 -autoconfirm

     */

    create_t* creatBPOSInstance = (create_t*) dlsym(lib, "create");
    const char* dlsym_error = dlerror();
    if(dlsym_error) {
        while(1) {

        }
        cout << "Cannot load symbol create: " << dlsym_error << endl;
        return;
    }

    destroy_t* destroyBPOSInstance = (destroy_t*) dlsym(lib, "destroy");
    dlsym_error = dlerror();
    if(dlsym_error)
    {
        cout << "Cannot load symbol destroy: " << dlsym_error << endl;
        return;
    }

    CBPOSClient *pBPOSClient = creatBPOSInstance();

   // Params parameters;
    if (parameters.bIsConsoleOn)
    {
        cout << "COM port configuration " << endl;
        cout << "0. CommOpen() " << endl;
        cout << "1. CommOpenTCP() " << endl;
        #ifdef _UDEV
            cout << "2. CommOpenAuto() " << endl;
        #endif
        cin >> parameters.nCommOpt;
        if (parameters.nCommOpt == 0)
        {
            cout << "Port name: ";
            cin >> parameters.sPort;
            cout << "Baud rate: ";
            cin >> parameters.nBaudRate;
        }else if (parameters.nCommOpt == 1)
        {
            cout << "IP: ";
            cin >> parameters.sIP;
            cout << "Port: ";
            cin >> parameters.sPort;
        }
        #ifdef _UDEV
            else if (parameters.nCommOpt == 2)
            {
                cout << "Baud rate: ";
                cin >> parameters.nBaudRate;
            }
        #endif
    }
    cout << "useLogging()..." << endl;
    pBPOSClient->useLogging(2, "logbpos.txt");
    cout << "SetErrorLang...." << endl;
    int rc = pBPOSClient->SetErrorLang(static_cast<int>(parameters.bErrorLang));
    cout << "SetErrorLang... OK" << endl;
    do
    {
        if(!pBPOSClient)
            break;
        if (parameters.bIsConsoleOn)
            PritFunctList();

        Scenarios scenarion = static_cast<Scenarios>(parameters.nTrnType);
        if (parameters.bIsConsoleOn)
        {
            cout << "Test with scenario (1/2/3/4/5/6/7/8/9/10/11/12/13/14/15/16/17/18/19/20/21/22/23/24/25/26/27/28/29/30/31/32/33/34/35/36/37/38)";
            try
            {
                cin >> scenarion;
            } catch ( out_of_range& ex )
            {
                cerr << ex.what() <<endl;
            }
        }
        cout << "CommClose... " << endl;
        char sError[128];
        unsigned char ucErrorCode = ECRC_OK;
        rc = pBPOSClient->CommClose();
        cout << "CommClose... OK" << endl;
        if (parameters.nCommOpt == 0){
            cout << "CommOpen..." << endl;
            rc = pBPOSClient->CommOpen(parameters.sPort.c_str(), parameters.nBaudRate);
            cout << "CommOpen... OK" << endl;
        }
        else if (parameters.nCommOpt == 1)
            rc = pBPOSClient->CommOpenTCP(parameters.sIP.c_str(), parameters.sPort.c_str());
        #ifdef _UDEV
        else
            rc = pBPOSClient->CommOpenAuto(parameters.nBaudRate);
        #endif

        cout << "get_LastResult()..." << endl;
        unsigned char ucLastResult = 0;
        pBPOSClient->get_LastResult(ucLastResult);
        cout << "LastResult = " <<  static_cast<int>(ucLastResult) << endl;
        if (PrintInfo(rc, pBPOSClient))
            break;

        time_t start_time = time(0);
        rc = RunScenario(scenarion, pBPOSClient, parameters, start_time);
        if (PrintInfo(rc, pBPOSClient))
            continue;

        switch (scenarion)
        {
        case SetExtraPrintData:
        case SetExtraXmlData:
        case useLogging:
            continue;
        }

        WaitResAndFinish(scenarion, pBPOSClient, parameters);

        if (parameters.bIsAutoConfirm)
        {
            cout << " === AUTOCONFIRM === " << endl;
            rc = RunScenario(Confirm, pBPOSClient, parameters, start_time);
            if (PrintInfo(rc, pBPOSClient))
                continue;

            WaitResAndFinish(scenarion, pBPOSClient, parameters);
        }
    }
    while(true && parameters.bIsConsoleOn);

    //destroy the instance of GTBClient
    destroyBPOSInstance(pBPOSClient);


    //unload the library
    //serialPort.closeSerialPort();



}

void BPosLib::init()
{
    //load BPOSLib
    lib = dlopen("libBPOSLib.so", RTLD_LAZY);
    if(!lib) {
        std::cout << "Cannot load library: " << dlerror() << std::endl;
        return;
    }

    //reset errors
    dlerror();

    //load the symbols




   // m_pBPOSClient = creatBPOSInstance();


}
