#include "InterfacesWidget.h"
#include "ui_InterfacesWidget.h"

//-------------------------------------------------------------------------------------------------
InterfacesWidget::InterfacesWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::InterfacesWidget)
{
    m_ui->setupUi(this);
}
//-------------------------------------------------------------------------------------------------
InterfacesWidget::~InterfacesWidget()
{
    delete m_ui;
}
//-------------------------------------------------------------------------------------------------
