#include "ExpensionBoardData.h"

//-------------------------------------------------------------------------------------------------
ExpensionBoardData::ExpensionBoardData(QObject *parent)
    : QObject(parent)
    , m_modbusAddress(" test")
    , m_isEnable(false)
{
    initInputs();
    initOutputs();
    initDispensers();
    initSensors();
}
//-------------------------------------------------------------------------------------------------
QHash<int, Input *> ExpensionBoardData::getInputs() const
{
    return m_inputs;
}
//-------------------------------------------------------------------------------------------------
QHash<int, Output *> ExpensionBoardData::getOutputs() const
{
    return m_outputs;
}
//-------------------------------------------------------------------------------------------------
QHash<int, Sensor *> ExpensionBoardData::getSensors() const
{
    return m_sensors;
}
//-------------------------------------------------------------------------------------------------
QHash<int, Dispenser *> ExpensionBoardData::getDispensers() const
{
    return m_dispensers;
}
//-------------------------------------------------------------------------------------------------
int ExpensionBoardData::getInputValue(int ndx) const
{
    Input *input = m_inputs.value(ndx);
    if (input == nullptr)
        return 0;

    return input->getValue();
}
//-------------------------------------------------------------------------------------------------
void ExpensionBoardData::setInputValue(int ndx, int value)
{
    Input *input = m_inputs.value(ndx);
    if (input == nullptr)
        return;

    input->setValue(value);
}
//-------------------------------------------------------------------------------------------------
int ExpensionBoardData::getOutputValue(int ndx) const
{
    Output *output = m_outputs.value(ndx);
    if (output == nullptr)
        return 0;

    return output->getValue();
}
//-------------------------------------------------------------------------------------------------
void ExpensionBoardData::setOutputValue(int ndx, int value)
{
    Output *output = m_outputs.value(ndx);
    if (output == nullptr)
        return;

    output->setValue(value);
}
//-------------------------------------------------------------------------------------------------
int ExpensionBoardData::getDispenserFrequency(int ndx) const
{
    Dispenser *dispenser = m_dispensers.value(ndx);
    if (dispenser == nullptr)
        return 0;

    return dispenser->getFrequency();
}
//-------------------------------------------------------------------------------------------------
int ExpensionBoardData::getDispenserFilling(int ndx) const
{
    Dispenser *dispenser = m_dispensers.value(ndx);
    if (dispenser == nullptr)
        return 0;

    return dispenser->getFilling();
}
//-------------------------------------------------------------------------------------------------
void ExpensionBoardData::setDispenserFrequency(int ndx, int value)
{
    Dispenser *dispenser = m_dispensers.value(ndx);
    if (dispenser == nullptr)
        return;

    dispenser->setFrequency(value);
}
//-------------------------------------------------------------------------------------------------
void ExpensionBoardData::setDispenserFilling(int ndx, int value)
{
    Dispenser *dispenser = m_dispensers.value(ndx);
    if (dispenser == nullptr)
        return;

    dispenser->setFilling(value);
}
//-------------------------------------------------------------------------------------------------
int ExpensionBoardData::getSensorType(int ndx) const
{
    Sensor *sensor = m_sensors.value(ndx);
    if (sensor == nullptr)
        return 0;

    return sensor->getType();
}
//-------------------------------------------------------------------------------------------------
int ExpensionBoardData::getSensorPulses(int ndx) const
{
    Sensor *sensor = m_sensors.value(ndx);
    if (sensor == nullptr)
        return 0;

    return sensor->getPulses();
}
//-------------------------------------------------------------------------------------------------
void ExpensionBoardData::setSensorType(int ndx, int value)
{
    Sensor *sensor = m_sensors.value(ndx);
    if (sensor == nullptr)
        return;

    sensor->setType(value);
}
//-------------------------------------------------------------------------------------------------
void ExpensionBoardData::setSensorPulses(int ndx, int value)
{
    Sensor *sensor = m_sensors.value(ndx);
    if (sensor == nullptr)
        return;

    sensor->setPulses(value);
}
//-------------------------------------------------------------------------------------------------
void ExpensionBoardData::setModbussAddress(const QString &address)
{
    m_modbusAddress = address;
}
//-------------------------------------------------------------------------------------------------
QString ExpensionBoardData::getModbusAddress() const
{
    return m_modbusAddress;
}
//-------------------------------------------------------------------------------------------------
void ExpensionBoardData::setEnable(bool enabled)
{
    m_isEnable = enabled;
}
//-------------------------------------------------------------------------------------------------
bool ExpensionBoardData::isEnable() const
{
    return m_isEnable;
}
//-------------------------------------------------------------------------------------------------
void ExpensionBoardData::initInputs()
{
    m_inputs.insert(1, new Input(1, 0));
    m_inputs.insert(2, new Input(2, 0));
    m_inputs.insert(3, new Input(3, 0));
    m_inputs.insert(4, new Input(4, 0));
    m_inputs.insert(5, new Input(5, 0));
    m_inputs.insert(6, new Input(6, 0));
    m_inputs.insert(7, new Input(7, 0));
    m_inputs.insert(8, new Input(8, 0));
}
//-------------------------------------------------------------------------------------------------
void ExpensionBoardData::initOutputs()
{
    m_outputs.insert(1, new Output(1, 0));
    m_outputs.insert(2, new Output(2, 0));
    m_outputs.insert(3, new Output(3, 0));
    m_outputs.insert(4, new Output(4, 0));
    m_outputs.insert(5, new Output(5, 0));
    m_outputs.insert(6, new Output(6, 0));
    m_outputs.insert(7, new Output(7, 0));
    m_outputs.insert(8, new Output(8, 0));
    m_outputs.insert(9, new Output(9, 0));
    m_outputs.insert(10, new Output(10, 0));
    m_outputs.insert(11, new Output(11, 0));
    m_outputs.insert(12, new Output(12, 0));
    m_outputs.insert(13, new Output(13, 0));
    m_outputs.insert(14, new Output(14, 0));
    m_outputs.insert(15, new Output(15, 0));
    m_outputs.insert(16, new Output(16, 0));
    m_outputs.insert(17, new Output(17, 0));
    m_outputs.insert(18, new Output(18, 0));
    m_outputs.insert(19, new Output(19, 0));
    m_outputs.insert(20, new Output(20, 0));
    m_outputs.insert(21, new Output(21, 0));
    m_outputs.insert(22, new Output(22, 0));
    m_outputs.insert(23, new Output(23, 0));
    m_outputs.insert(24, new Output(24, 0));
    m_outputs.insert(25, new Output(25, 0));
    m_outputs.insert(26, new Output(26, 0));
    m_outputs.insert(27, new Output(27, 0));
    m_outputs.insert(28, new Output(28, 0));
}
//-------------------------------------------------------------------------------------------------
void ExpensionBoardData::initDispensers()
{
    m_dispensers.insert(1, new Dispenser(1, 0, 0));
    m_dispensers.insert(2, new Dispenser(2, 0, 0));
    m_dispensers.insert(3, new Dispenser(3, 0, 0));
    m_dispensers.insert(4, new Dispenser(4, 0, 0));
}
//-------------------------------------------------------------------------------------------------
void ExpensionBoardData::initSensors()
{
    m_sensors.insert(1, new Sensor(1, 0, 0));
    m_sensors.insert(2, new Sensor(2, 0, 0));
    m_sensors.insert(3, new Sensor(3, 0, 0));
    m_sensors.insert(4, new Sensor(4, 0, 0));
}
//-------------------------------------------------------------------------------------------------
