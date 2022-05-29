#include "OptionsWidget.h"
#include "ui_OptionsWidget.h"

//-------------------------------------------------------------------------------------------------
OptionsWidget::OptionsWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::OptionsWidget)
{
    m_ui->setupUi(this);
}
//-------------------------------------------------------------------------------------------------
OptionsWidget::~OptionsWidget()
{
    delete m_ui;
}
//-------------------------------------------------------------------------------------------------
