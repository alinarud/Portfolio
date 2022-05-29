#ifndef PAYMENTDEVICESWIDGET_H
#define PAYMENTDEVICESWIDGET_H

#include <QWidget>

namespace Ui {
class PaymentDevicesWidget;
}

class PaymentDevicesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PaymentDevicesWidget(QWidget *parent = nullptr);
    ~PaymentDevicesWidget();

private:
    Ui::PaymentDevicesWidget *m_ui;
};

#endif // PAYMENTDEVICESWIDGET_H
