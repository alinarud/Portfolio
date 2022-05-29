#include "MainBoardData.h"

//-------------------------------------------------------------------------------------------------
MainBoardData::MainBoardData(QObject *parent) : QObject(parent)
{
    initInputs();
    initOutputs();
    initDispensers();
    initSensors();
}
//-------------------------------------------------------------------------------------------------
QHash<int, Input *> MainBoardData::getInputs() const
{
    return m_inputs;
}
//-------------------------------------------------------------------------------------------------
QHash<int, Output *> MainBoardData::getOutputs() const
{
    return m_outputs;
}
//-------------------------------------------------------------------------------------------------
QHash<int, Sensor *> MainBoardData::getSensors() const
{
    return m_sensors;
}
//-------------------------------------------------------------------------------------------------
QHash<int, Dispenser *> MainBoardData::getDispensers() const
{
    return m_dispensers;
}
//-------------------------------------------------------------------------------------------------
int MainBoardData::getInputValue(int ndx) const
{
    Input *input = m_inputs.value(ndx);
    if (input == nullptr)
        return 0;

    return input->getValue();
}
//-------------------------------------------------------------------------------------------------
void MainBoardData::setInputValue(int ndx, int value)
{
    Input *input = m_inputs.value(ndx);
    if (input == nullptr)
        return;

    input->setValue(value);
}
//-------------------------------------------------------------------------------------------------
int MainBoardData::getOutputValue(int ndx) const
{
    Output *output = m_outputs.value(ndx);
    if (output == nullptr)
        return 0;

    return output->getValue();
}
//-------------------------------------------------------------------------------------------------
void MainBoardData::setOutputValue(int ndx, int value)
{
    Output *output = m_outputs.value(ndx);
    if (output == nullptr)
        return;

    output->setValue(value);
}
//-------------------------------------------------------------------------------------------------
int MainBoardData::getDispenserFrequency(int ndx) const
{
    Dispenser *dispenser = m_dispensers.value(ndx);
    if (dispenser == nullptr)
        return 0;

    return dispenser->getFrequency();
}
//-------------------------------------------------------------------------------------------------
int MainBoardData::getDispenserFilling(int ndx) const
{
    Dispenser *dispenser = m_dispensers.value(ndx);
    if (dispenser == nullptr)
        return 0;

    return dispenser->getFilling();
}
//-------------------------------------------------------------------------------------------------
void MainBoardData::setDispenserFrequency(int ndx, int value)
{
    Dispenser *dispenser = m_dispensers.value(ndx);
    if (dispenser == nullptr)
        return;

    dispenser->setFrequency(value);
}
//-------------------------------------------------------------------------------------------------
void MainBoardData::setDispenserFilling(int ndx, int value)
{
    Dispenser *dispenser = m_dispensers.value(ndx);
    if (dispenser == nullptr)
        return;

    dispenser->setFilling(value);
}
//-------------------------------------------------------------------------------------------------
int MainBoardData::getSensorType(int ndx) const
{
    Sensor *sensor = m_sensors.value(ndx);
    if (sensor == nullptr)
        return 0;

    return sensor->getType();
}
//-------------------------------------------------------------------------------------------------
int MainBoardData::getSensorPulses(int ndx) const
{
    Sensor *sensor = m_sensors.value(ndx);
    if (sensor == nullptr)
        return 0;

    return sensor->getPulses();
}
//-------------------------------------------------------------------------------------------------
void MainBoardData::setSensorType(int ndx, int value)
{
    Sensor *sensor = m_sensors.value(ndx);
    if (sensor == nullptr)
        return;

    sensor->setType(value);
}
//-------------------------------------------------------------------------------------------------
void MainBoardData::setSensorPulses(int ndx, int value)
{
    Sensor *sensor = m_sensors.value(ndx);
    if (sensor == nullptr)
        return;

    sensor->setPulses(value);
}
//-------------------------------------------------------------------------------------------------
void MainBoardData::initInputs()
{
    m_inputs.insert(1, new Input(1, 0));
    m_inputs.insert(2, new Input(2, 0));
    m_inputs.insert(3, new Input(3, 0));
    m_inputs.insert(4, new Input(4, 0));
    m_inputs.insert(5, new Input(5, 0));
    m_inputs.insert(6, new Input(6, 0));
    m_inputs.insert(7, new Input(7, 0));
    m_inputs.insert(8, new Input(8, 0));
    m_inputs.insert(9, new Input(9, 0));
    m_inputs.insert(10, new Input(10, 0));
    m_inputs.insert(11, new Input(11, 0));
    m_inputs.insert(12, new Input(12, 0));
    m_inputs.insert(13, new Input(13, 0));
    m_inputs.insert(14, new Input(14, 0));
    m_inputs.insert(15, new Input(15, 0));
    m_inputs.insert(16, new Input(16, 0));
}
//-------------------------------------------------------------------------------------------------
void MainBoardData::initOutputs()
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
}
//-------------------------------------------------------------------------------------------------
void MainBoardData::initDispensers()
{
    m_dispensers.insert(1, new Dispenser(1, 0, 0));
    m_dispensers.insert(2, new Dispenser(2, 0, 0));
    m_dispensers.insert(3, new Dispenser(3, 0, 0));
    m_dispensers.insert(4, new Dispenser(4, 0, 0));
}
//-------------------------------------------------------------------------------------------------
void MainBoardData::initSensors()
{
    m_sensors.insert(1, new Sensor(1, 0, 0));
    m_sensors.insert(2, new Sensor(2, 0, 0));
    m_sensors.insert(3, new Sensor(3, 0, 0));
    m_sensors.insert(4, new Sensor(4, 0, 0));
}
//-------------------------------------------------------------------------------------------------
