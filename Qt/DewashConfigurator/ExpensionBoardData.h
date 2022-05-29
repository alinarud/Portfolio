#ifndef EXPENSIONBOARDDATA_H
#define EXPENSIONBOARDDATA_H

#include <QObject>
#include <QHash>

#include "Input.h"
#include "Output.h"
#include "Sensor.h"
#include "Dispenser.h"

class ExpensionBoardData : public QObject
{
    Q_OBJECT
public:
    explicit ExpensionBoardData(QObject *parent = nullptr);

public slots:
    QHash<int, Input*> getInputs() const;
    QHash<int, Output*> getOutputs() const;
    QHash<int, Sensor*> getSensors() const;
    QHash<int, Dispenser*> getDispensers() const;
    int getInputValue(int ndx) const;
    void setInputValue(int ndx, int value);
    int getOutputValue(int ndx) const;
    void setOutputValue(int ndx, int value);
    int getDispenserFrequency(int ndx) const;
    int getDispenserFilling(int ndx) const;
    void setDispenserFrequency(int ndx, int value);
    void setDispenserFilling(int ndx, int value);
    int getSensorType(int ndx) const;
    int getSensorPulses(int ndx) const;
    void setSensorType(int ndx, int value);
    void setSensorPulses(int ndx, int value);
    void setModbussAddress(const QString &address);
    QString getModbusAddress() const;
    void setEnable(bool enabled);
    bool isEnable() const;

private:
    void initInputs();
    void initOutputs();
    void initDispensers();
    void initSensors();

private:
    QString                 m_modbusAddress;
    bool                    m_isEnable;
    QHash<int, Input*>      m_inputs;
    QHash<int, Output*>     m_outputs;
    QHash<int, Sensor*>     m_sensors;
    QHash<int, Dispenser*>  m_dispensers;

};

#endif // EXPENSIONBOARDDATA_H
