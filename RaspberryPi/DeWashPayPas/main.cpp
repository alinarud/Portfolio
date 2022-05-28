#include <QCoreApplication>

#include <iostream>
#include <QThread>
#include "SerialPort.h"
#include "DataManager.h"
#include "BPosManager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "DeWash PayPas app started" << std::endl;

    DataManager::getInstance(); // init
    QThread portThread;
    SerialPort *port = new SerialPort();
    port->moveToThread(&portThread);

    QObject::connect(&portThread,    &QThread::finished, port, &SerialPort::deleteLater);

    portThread.start();

    int result = a.exec();

    DataManager::shut();

    return result;
}
