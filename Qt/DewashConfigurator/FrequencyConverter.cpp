#include "FrequencyConverter.h"

//-------------------------------------------------------------------------------------------------
FrequencyConverter::FrequencyConverter(int index, const QString &modbusAddress, QObject *parent)
    : QObject(parent)
    , m_index(index)
    , m_modbusAddress(modbusAddress)
{

}
//-------------------------------------------------------------------------------------------------
void FrequencyConverter::setIndex(int ndx)
{
    m_index = ndx;
}
//-------------------------------------------------------------------------------------------------
int FrequencyConverter::getIndex() const
{
    return m_index;
}
//-------------------------------------------------------------------------------------------------
void FrequencyConverter::setModbusAddress(const QString &modbusAddress)
{
    m_modbusAddress = modbusAddress;
}
//-------------------------------------------------------------------------------------------------
QString FrequencyConverter::getModbusAddress() const
{
    return m_modbusAddress;
}
//-------------------------------------------------------------------------------------------------
