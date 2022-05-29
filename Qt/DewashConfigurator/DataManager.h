#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QDomDocument>
#include <QDomElement>

#include "MainBoardData.h"
#include "ExpensionBoardData.h"
#include "Sensor.h"

#define DATA_MANAGER()                   (DataManager::getInstance())


class DataManager
{
protected:
    DataManager();
    ~DataManager();

public:
    static DataManager *getInstance();
    static void    shut();

    int getMainBoardInputValue(int ndx) const;
    void setMainBoardInputValue(int ndx, int value);
    int getMainBoardOutputValue(int ndx) const;
    void setMainBoardOutputValue(int ndx, int value);
    int getMainBoardDispenserFrequency(int ndx) const;
    int getMainBoardDispenserFilling(int ndx) const;
    void setMainBoardDispenserFrequency(int ndx, int value);
    void setMainBoardDispenserFilling(int ndx, int value);
    int getMainBoardSensorType(int ndx) const;
    int getMainBoardSensorPulses(int ndx) const;
    void setMainBoardSensorType(int ndx, int value);
    void setMainBoardSensorPulses(int ndx, int value);
    QString getFreqConverterModbusAddr(int ndx) const;
    void setFreqConverterModbusAddr(int ndx, const QString &value);
    int getExpensionBoardInputValue(int ndx) const;
    void setExpensionBoardInputValue(int ndx, int value);
    int getExpensionBoardOutputValue(int ndx) const;
    void setExpensionBoardOutputValue(int ndx, int value);
    int getExpensionBoardDispenserFrequency(int ndx) const;
    int getExpensionBoardDispenserFilling(int ndx) const;
    void setExpensionBoardDispenserFrequency(int ndx, int value);
    void setExpensionBoardDispenserFilling(int ndx, int value);
    int getExpensionBoardSensorType(int ndx) const;
    int getExpensionBoardSensorPulses(int ndx) const;
    void setExpensionBoardSensorType(int ndx, int value);
    void setExpensionBoardSensorPulses(int ndx, int value);
    void setExpensionBoardModbusAddress(const QString &address);
    QString getExpensionBoardModbusAddress() const;

public slots:
    void onSaveData2File(const QString &path);
    void onLoadDataFromFile(const QString &path);

private:
    void initFrequencyConverters();
    void saveMainBoardData(QDomDocument &document, QDomElement &parent);
    void saveExpensionBoardData(QDomDocument &document, QDomElement &parent);
    void saveFrequencyConvertersData(QDomDocument &document, QDomElement &parent);
    QDomElement getInputsDomElement(QDomDocument &document, const QHash<int, Input*> &inputs);
    QDomElement getOutputsDomElement(QDomDocument &document, const QHash<int, Output*> &outputs);
    QDomElement getSensorsDomElement(QDomDocument &document, const QHash<int, Sensor*> &sensors);
    QDomElement getDispensersDomElement(QDomDocument &document, const QHash<int, Dispenser*> &dispensers);

private:
    static DataManager              *m_dataManager;
    MainBoardData                   *m_mainBoardData;
    ExpensionBoardData              *m_expensionBoardData;
    QHash<int, FrequencyConverter*>  m_frequencyConverters;

};

#endif // DATAMANAGER_H
