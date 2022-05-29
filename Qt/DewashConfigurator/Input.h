#ifndef INPUT_H
#define INPUT_H

#include <QObject>

class Input : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int index READ getIndex WRITE setIndex NOTIFY indexChanged)
public:
    explicit Input(int ndx, int value, QObject *parent = nullptr);
    Input(QObject *parent = nullptr);

    void setIndex(int ndx);
    int getIndex() const;
    void setValue(int value);
    int getValue() const;

signals:
    void indexChanged();

private:
    int     m_index;
    int     m_value;
};

#endif // INPUT_H
