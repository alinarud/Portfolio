#ifndef INTERFACESWIDGET_H
#define INTERFACESWIDGET_H

#include <QWidget>

namespace Ui {
class InterfacesWidget;
}

class InterfacesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InterfacesWidget(QWidget *parent = nullptr);
    ~InterfacesWidget();

private:
    Ui::InterfacesWidget *m_ui;
};

#endif // INTERFACESWIDGET_H
