#include "Dispenser.h"

//-------------------------------------------------------------------------------------------------
Dispenser::Dispenser(int ndx, int frequency, int filling, bool enable, QObject *parent)
    : QObject(parent)
    , m_index(ndx)
    , m_enable(enable)
    , m_frequency(frequency)
    , m_filling(filling)
{

}
//-------------------------------------------------------------------------------------------------
void Dispenser::setIndex(int ndx)
{
    m_index = ndx;
}
//-------------------------------------------------------------------------------------------------
int Dispenser::getIndex() const
{
    return m_index;
}
//-------------------------------------------------------------------------------------------------
void Dispenser::setFrequency(int frequency)
{
    m_frequency = frequency;
}
//-------------------------------------------------------------------------------------------------
int Dispenser::getFrequency() const
{
    return m_frequency;
}
//-------------------------------------------------------------------------------------------------
void Dispenser::setFilling(int filling)
{
    m_filling = filling;
}
//-------------------------------------------------------------------------------------------------
int Dispenser::getFilling() const
{
    return m_filling;
}
//-------------------------------------------------------------------------------------------------
void Dispenser::setEnable(bool enabled)
{
    m_enable = enabled;
}
//-------------------------------------------------------------------------------------------------
bool Dispenser::isEnable() const
{
    return m_enable;
}
//-------------------------------------------------------------------------------------------------
