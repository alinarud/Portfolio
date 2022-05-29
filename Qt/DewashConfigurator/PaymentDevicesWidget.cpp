#include "PaymentDevicesWidget.h"
#include "ui_PaymentDevicesWidget.h"

//-------------------------------------------------------------------------------------------------
PaymentDevicesWidget::PaymentDevicesWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::PaymentDevicesWidget)
{
    m_ui->setupUi(this);
}
//-------------------------------------------------------------------------------------------------
PaymentDevicesWidget::~PaymentDevicesWidget()
{
    delete m_ui;
}
//-------------------------------------------------------------------------------------------------
