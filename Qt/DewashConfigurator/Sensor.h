#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>

class   Sensor : public QObject
{
    Q_OBJECT
public:
    explicit Sensor(int ndx, int type, int pulses, bool enable = true, QObject *parent = nullptr);

    void setIndex(int ndx);
    int getIndex() const;
    void setType(int type);
    int getType() const;
    void setPulses(int pulses);
    int getPulses() const;
    void setEnable(bool enable);
    bool isEnable() const;

private:
    int     m_index;
    int     m_type;
    int     m_pulses;
    bool    m_enable;
};

#endif // SENSOR_H
