#ifndef FREQUENCYCONVERTER_H
#define FREQUENCYCONVERTER_H

#include <QObject>

class FrequencyConverter : public QObject
{
    Q_OBJECT
public:
    explicit FrequencyConverter(int index, const QString &modbusAddress, QObject *parent = nullptr);

    void setIndex(int ndx);
    int getIndex() const;
    void setModbusAddress(const QString &modbusAddress);
    QString getModbusAddress() const;

private:
    int     m_index;
    QString m_modbusAddress;
};

#endif // FREQUENCYCONVERTER_H
