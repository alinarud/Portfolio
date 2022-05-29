#include "MainWindow.h"
#include "DataManager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DataManager::shut();

    return a.exec();
}
