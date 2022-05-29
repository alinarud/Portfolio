#include "DataManager.h"
#include "Constants.h"

#include <QDebug>
#include <QDir>

DataManager *DataManager::m_dataManager;


//-------------------------------------------------------------------------------------------------
DataManager::DataManager()
{
    m_mainBoardData = new MainBoardData();
    m_expensionBoardData = new ExpensionBoardData();

    initFrequencyConverters();
}
//-------------------------------------------------------------------------------------------------
DataManager::~DataManager()
{
    if (m_mainBoardData != nullptr) {
        delete m_mainBoardData;
        m_mainBoardData = nullptr;
    }
    if (m_expensionBoardData != nullptr) {
        delete m_expensionBoardData;
        m_expensionBoardData = nullptr;
    }
}
//-------------------------------------------------------------------------------------------------
DataManager *DataManager::getInstance()
{
    if (m_dataManager == nullptr)
        m_dataManager = new DataManager();

    return m_dataManager;
}
//-------------------------------------------------------------------------------------------------
void DataManager::shut()
{
    if (m_dataManager != nullptr) {
        delete m_dataManager;
        m_dataManager = nullptr;
    }
}
//-------------------------------------------------------------------------------------------------
int DataManager::getMainBoardInputValue(int ndx) const
{
    if (m_mainBoardData == nullptr)
        return 0;

    return m_mainBoardData->getInputValue(ndx);
}
//-------------------------------------------------------------------------------------------------
void DataManager::setMainBoardInputValue(int ndx, int value)
{
    if (m_mainBoardData != nullptr)
        m_mainBoardData->setInputValue(ndx, value);
}
//-------------------------------------------------------------------------------------------------
int DataManager::getMainBoardOutputValue(int ndx) const
{
    if (m_mainBoardData == nullptr)
        return 0;

    return m_mainBoardData->getOutputValue(ndx);
}
//-------------------------------------------------------------------------------------------------
void DataManager::setMainBoardOutputValue(int ndx, int value)
{
    if (m_mainBoardData != nullptr)
        m_mainBoardData->setOutputValue(ndx, value);
}
//-------------------------------------------------------------------------------------------------
int DataManager::getMainBoardDispenserFrequency(int ndx) const
{
    if (m_mainBoardData == nullptr)
        return 0;

    return m_mainBoardData->getDispenserFrequency(ndx);
}
//-------------------------------------------------------------------------------------------------
int DataManager::getMainBoardDispenserFilling(int ndx) const
{
    if (m_mainBoardData == nullptr)
        return 0;

    return m_mainBoardData->getDispenserFilling(ndx);
}
//-------------------------------------------------------------------------------------------------
void DataManager::setMainBoardDispenserFrequency(int ndx, int value)
{
    if (m_mainBoardData != nullptr)
        m_mainBoardData->setDispenserFrequency(ndx, value);
}
//-------------------------------------------------------------------------------------------------
void DataManager::setMainBoardDispenserFilling(int ndx, int value)
{
    if (m_mainBoardData != nullptr)
        m_mainBoardData->setDispenserFilling(ndx, value);
}
//-------------------------------------------------------------------------------------------------
int DataManager::getMainBoardSensorType(int ndx) const
{
    if (m_mainBoardData == nullptr)
        return 0;

    return m_mainBoardData->getSensorType(ndx);
}
//-------------------------------------------------------------------------------------------------
int DataManager::getMainBoardSensorPulses(int ndx) const
{
    if (m_mainBoardData == nullptr)
        return 0;

    return m_mainBoardData->getSensorPulses(ndx);
}
//-------------------------------------------------------------------------------------------------
void DataManager::setMainBoardSensorType(int ndx, int value)
{
    if (m_mainBoardData != nullptr)
        m_mainBoardData->setSensorType(ndx, value);
}
//-------------------------------------------------------------------------------------------------
void DataManager::setMainBoardSensorPulses(int ndx, int value)
{
    if (m_mainBoardData != nullptr)
        m_mainBoardData->setSensorPulses(ndx, value);
}
//-------------------------------------------------------------------------------------------------
QString DataManager::getFreqConverterModbusAddr(int ndx) const
{
    FrequencyConverter *converter = m_frequencyConverters.value(ndx);
    if (converter == nullptr)
        return "";

    return converter->getModbusAddress();
}
//-------------------------------------------------------------------------------------------------
void DataManager::setFreqConverterModbusAddr(int ndx, const QString &value)
{
    FrequencyConverter *converter = m_frequencyConverters.value(ndx);
    if (converter == nullptr)
        return;

    converter->setModbusAddress(value);
}
//-------------------------------------------------------------------------------------------------
int DataManager::getExpensionBoardInputValue(int ndx) const
{
    if (m_expensionBoardData == nullptr)
        return 0;

    return m_expensionBoardData->getInputValue(ndx);
}
//-------------------------------------------------------------------------------------------------
void DataManager::setExpensionBoardInputValue(int ndx, int value)
{
    if (m_expensionBoardData != nullptr)
        m_expensionBoardData->setInputValue(ndx, value);
}
//-------------------------------------------------------------------------------------------------
int DataManager::getExpensionBoardOutputValue(int ndx) const
{
    if (m_expensionBoardData == nullptr)
        return 0;

    return m_expensionBoardData->getOutputValue(ndx);
}
//-------------------------------------------------------------------------------------------------
void DataManager::setExpensionBoardOutputValue(int ndx, int value)
{
    if (m_expensionBoardData != nullptr)
        m_expensionBoardData->setOutputValue(ndx, value);
}
//-------------------------------------------------------------------------------------------------
int DataManager::getExpensionBoardDispenserFrequency(int ndx) const
{
    if (m_expensionBoardData == nullptr)
        return 0;

    return m_expensionBoardData->getDispenserFrequency(ndx);
}
//-------------------------------------------------------------------------------------------------
int DataManager::getExpensionBoardDispenserFilling(int ndx) const
{
    if (m_expensionBoardData == nullptr)
        return 0;

    return m_expensionBoardData->getDispenserFilling(ndx);
}
//-------------------------------------------------------------------------------------------------
void DataManager::setExpensionBoardDispenserFrequency(int ndx, int value)
{
    if (m_expensionBoardData != nullptr)
        m_expensionBoardData->setDispenserFrequency(ndx, value);
}
//-------------------------------------------------------------------------------------------------
void DataManager::setExpensionBoardDispenserFilling(int ndx, int value)
{
    if (m_expensionBoardData != nullptr)
        m_expensionBoardData->setDispenserFilling(ndx, value);
}
//-------------------------------------------------------------------------------------------------
int DataManager::getExpensionBoardSensorType(int ndx) const
{
    if (m_expensionBoardData == nullptr)
        return 0;

    return m_expensionBoardData->getSensorType(ndx);
}
//-------------------------------------------------------------------------------------------------
int DataManager::getExpensionBoardSensorPulses(int ndx) const
{
    if (m_expensionBoardData == nullptr)
        return 0;

    return m_expensionBoardData->getSensorPulses(ndx);
}
//-------------------------------------------------------------------------------------------------
void DataManager::setExpensionBoardSensorType(int ndx, int value)
{
    if (m_expensionBoardData != nullptr)
        m_expensionBoardData->setSensorType(ndx, value);
}
//-------------------------------------------------------------------------------------------------
void DataManager::setExpensionBoardSensorPulses(int ndx, int value)
{
    if (m_expensionBoardData != nullptr)
        m_expensionBoardData->setSensorPulses(ndx, value);
}
//-------------------------------------------------------------------------------------------------
void DataManager::setExpensionBoardModbusAddress(const QString &address)
{
    if (m_expensionBoardData != nullptr)
        m_expensionBoardData->setModbussAddress(address);
}
//-------------------------------------------------------------------------------------------------
QString DataManager::getExpensionBoardModbusAddress() const
{
    if (m_expensionBoardData == nullptr)
        return 0;

    return m_expensionBoardData->getModbusAddress();
}
//-------------------------------------------------------------------------------------------------
void DataManager::onSaveData2File(const QString &path)
{
    QDomDocument document(path);
    document.clear();
    QDomNode node = document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
    document.appendChild(node);

    QDomElement settingsElement = document.createElement(TagName::TAG_SETTINGS);

    saveFrequencyConvertersData(document, settingsElement);
    saveMainBoardData(document, settingsElement);
    saveExpensionBoardData(document, settingsElement);

    document.appendChild(settingsElement);

    QFile file(path);
    if(!file.open( QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug( "Failed to open file for writing." );
        return ;
    }

    QTextStream stream( &file );
    stream << document.toString();

    file.close();
}
//-------------------------------------------------------------------------------------------------
void DataManager::onLoadDataFromFile(const QString &path)
{

}
//-------------------------------------------------------------------------------------------------
void DataManager::initFrequencyConverters()
{
    m_frequencyConverters.insert(1, new FrequencyConverter(1, ""));
    m_frequencyConverters.insert(2, new FrequencyConverter(2, ""));
}
//-------------------------------------------------------------------------------------------------
void DataManager::saveMainBoardData(QDomDocument &document, QDomElement &parent)
{
    QDomElement mainBoardElement = document.createElement(TagName::TAG_MAIN_BOARD);

    // save main board inputs
    QHash<int, Input*> inputs = m_mainBoardData->getInputs();
    QDomElement mainBoardInputsElement = getInputsDomElement(document, inputs);

    // save main board outputs
    QHash<int, Output*> outputs = m_mainBoardData->getOutputs();
    QDomElement mainBoardOutputsElement = getOutputsDomElement(document, outputs);

    // save main board sensors
    QHash<int, Sensor*> sensors = m_mainBoardData->getSensors();
    QDomElement mainBoardSensorsElement = getSensorsDomElement(document, sensors);

    // save main board dispensers
    QHash<int, Dispenser*> dispensers = m_mainBoardData->getDispensers();
    QDomElement mainBoardDispensersElement = getDispensersDomElement(document, dispensers);

    mainBoardElement.appendChild(mainBoardInputsElement);
    mainBoardElement.appendChild(mainBoardOutputsElement);
    mainBoardElement.appendChild(mainBoardSensorsElement);
    mainBoardElement.appendChild(mainBoardDispensersElement);

    parent.appendChild(mainBoardElement);
}
//-------------------------------------------------------------------------------------------------
void DataManager::saveExpensionBoardData(QDomDocument &document, QDomElement &parent)
{
    QDomElement expensionBoardElement = document.createElement(TagName::TAG_EXPENSION_BOARD);
    expensionBoardElement.setAttribute(AttributeNames::ENABLE, m_expensionBoardData->isEnable() ? 1 : 0);
    expensionBoardElement.setAttribute(AttributeNames::MODBUS_ADDRESS, m_expensionBoardData->getModbusAddress());

    // save main board inputs
    QHash<int, Input*> inputs = m_expensionBoardData->getInputs();
    QDomElement expensionBoardInputsElement = getInputsDomElement(document, inputs);

    // save main board outputs
    QHash<int, Output*> outputs = m_expensionBoardData->getOutputs();
    QDomElement expensionBoardOutputsElement = getOutputsDomElement(document, outputs);

    // save main board sensors
    QHash<int, Sensor*> sensors = m_expensionBoardData->getSensors();
    QDomElement expensionBoardSensorsElement = getSensorsDomElement(document, sensors);

    // save main board dispensers
    QHash<int, Dispenser*> dispensers = m_expensionBoardData->getDispensers();
    QDomElement expensionBoardDispensersElement = getDispensersDomElement(document, dispensers);

    expensionBoardElement.appendChild(expensionBoardInputsElement);
    expensionBoardElement.appendChild(expensionBoardOutputsElement);
    expensionBoardElement.appendChild(expensionBoardSensorsElement);
    expensionBoardElement.appendChild(expensionBoardDispensersElement);

    parent.appendChild(expensionBoardElement);
}
//-------------------------------------------------------------------------------------------------
void DataManager::saveFrequencyConvertersData(QDomDocument &document, QDomElement &parent)
{
    QDomElement frequencyConvertersElement = document.createElement(TagName::TAG_FREQUENCY_CONVERTERS);

    QHashIterator<int, FrequencyConverter*> it(m_frequencyConverters);
    while (it.hasNext()) {
        it.next();
        FrequencyConverter *converter = it.value();
        if (converter == nullptr)
            continue;

        QDomElement converterElement = document.createElement(TagName::TAG_FREQUENCY_CONVERTER);
        converterElement.setAttribute(AttributeNames::INDEX, converter->getIndex());
        converterElement.setAttribute(AttributeNames::MODBUS_ADDRESS, converter->getModbusAddress());

        frequencyConvertersElement.appendChild(converterElement);
    }

    parent.appendChild(frequencyConvertersElement);
}
//-------------------------------------------------------------------------------------------------
QDomElement DataManager::getInputsDomElement(QDomDocument &document, const QHash<int, Input *> &inputs)
{
    QDomElement inputsElement = document.createElement(TagName::TAG_INPUTS);

    QHashIterator<int, Input*> itInputs(inputs);
    while (itInputs.hasNext()) {
        itInputs.next();
        Input *input = itInputs.value();
        if (input == nullptr)
            continue;

        QDomElement inputElement = document.createElement(TagName::TAG_INPUT);
        inputElement.setAttribute(AttributeNames::INDEX, input->getIndex());
        inputElement.setAttribute(AttributeNames::VALUE, input->getValue());

        inputsElement.appendChild(inputElement);
    }

    return inputsElement;
}
//-------------------------------------------------------------------------------------------------
QDomElement DataManager::getOutputsDomElement(QDomDocument &document, const QHash<int, Output *> &outputs)
{
    QDomElement outputsElement = document.createElement(TagName::TAG_OUTPUTS);

    QHashIterator<int, Output*> itOutputs(outputs);
    while (itOutputs.hasNext()) {
        itOutputs.next();
        Output *output = itOutputs.value();
        if (output == nullptr)
            continue;

        QDomElement outputElement = document.createElement(TagName::TAG_OUTPUT);
        outputElement.setAttribute(AttributeNames::INDEX, output->getIndex());
        outputElement.setAttribute(AttributeNames::VALUE, output->getValue());

        outputsElement.appendChild(outputElement);
    }

    return outputsElement;
}
//-------------------------------------------------------------------------------------------------
QDomElement DataManager::getSensorsDomElement(QDomDocument &document, const QHash<int, Sensor *> &sensors)
{
    QDomElement sensorsElement = document.createElement(TagName::TAG_SENSORS);

    QHashIterator<int, Sensor*> itSensors(sensors);
    while (itSensors.hasNext()) {
        itSensors.next();
        Sensor *sensor = itSensors.value();
        if (sensor == nullptr)
            continue;

        QDomElement sensorElement = document.createElement(TagName::TAG_SENSOR);
        sensorElement.setAttribute(AttributeNames::INDEX, sensor->getIndex());
        sensorElement.setAttribute(AttributeNames::TYPE, sensor->getType());
        sensorElement.setAttribute(AttributeNames::PULSES, sensor->getPulses());

        sensorsElement.appendChild(sensorElement);
    }

    return sensorsElement;
}
//-------------------------------------------------------------------------------------------------
QDomElement DataManager::getDispensersDomElement(QDomDocument &document, const QHash<int, Dispenser *> &dispensers)
{
    QDomElement dispensersElement = document.createElement(TagName::TAG_DISPENSERS);

    QHashIterator<int, Dispenser*> itDispensers(dispensers);
    while (itDispensers.hasNext()) {
        itDispensers.next();
        Dispenser *dispenser = itDispensers.value();
        if (dispenser == nullptr)
            continue;

        QDomElement dispenserElement = document.createElement(TagName::TAG_DISPENSER);
        dispenserElement.setAttribute(AttributeNames::INDEX, dispenser->getIndex());
        dispenserElement.setAttribute(AttributeNames::FREQUENCY, dispenser->getFrequency());
        dispenserElement.setAttribute(AttributeNames::FILLING, dispenser->getFilling());

        dispensersElement.appendChild(dispenserElement);
    }

    return dispensersElement;
}
//-------------------------------------------------------------------------------------------------
