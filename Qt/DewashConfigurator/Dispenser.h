#ifndef DISPENSER_H
#define DISPENSER_H

#include <QObject>

class Dispenser : public QObject
{
    Q_OBJECT
public:
    explicit Dispenser(int ndx, int frequency, int filling, bool enable = true, QObject *parent = nullptr);

    void setIndex(int ndx);
    int getIndex() const;
    void setFrequency(int frequency);
    int getFrequency() const;
    void setFilling(int filling);
    int getFilling() const;
    void setEnable(bool enabled);
    bool isEnable() const;

private:
    int     m_index;
    bool    m_enable;
    int     m_frequency;
    int     m_filling;
};

#endif // DISPENSER_H
