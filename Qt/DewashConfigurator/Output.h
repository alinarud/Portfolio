#ifndef OUTPUT_H
#define OUTPUT_H

#include <QObject>

class Output : public QObject
{
    Q_OBJECT
public:
    explicit Output(int ndx, int value, QObject *parent = nullptr);

    void setIndex(int ndx);
    int getIndex() const;
    void setValue(int value);
    int getValue() const;

private:
    int     m_index;
    int     m_value;
};

#endif // OUTPUT_H
