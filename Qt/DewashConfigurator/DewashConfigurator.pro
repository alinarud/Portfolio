QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AgregatesWidget.cpp \
    DataManager.cpp \
    Dispenser.cpp \
    ExpensionBoardData.cpp \
    FrequencyConverter.cpp \
    Input.cpp \
    InterfacesWidget.cpp \
    MainBoardData.cpp \
    OptionsWidget.cpp \
    Output.cpp \
    PaymentDevicesWidget.cpp \
    PrinterWidget.cpp \
    main.cpp \
    MainWindow.cpp \
    Sensor.cpp

HEADERS += \
    AgregatesWidget.h \
    Constants.h \
    DataManager.h \
    Dispenser.h \
    ExpensionBoardData.h \
    FrequencyConverter.h \
    Input.h \
    InterfacesWidget.h \
    MainBoardData.h \
    MainWindow.h \
    OptionsWidget.h \
    Output.h \
    PaymentDevicesWidget.h \
    PrinterWidget.h \
    Sensor.h

FORMS += \
    AgregatesWidget.ui \
    InterfacesWidget.ui \
    MainWindow.ui \
    OptionsWidget.ui \
    PaymentDevicesWidget.ui \
    PrinterWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourses.qrc
