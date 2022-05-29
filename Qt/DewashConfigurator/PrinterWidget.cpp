#include "PrinterWidget.h"
#include "ui_PrinterWidget.h"

//-------------------------------------------------------------------------------------------------
PrinterWidget::PrinterWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::PrinterWidget)
{
    m_ui->setupUi(this);
}
//-------------------------------------------------------------------------------------------------
PrinterWidget::~PrinterWidget()
{
    delete m_ui;
}
//-------------------------------------------------------------------------------------------------
