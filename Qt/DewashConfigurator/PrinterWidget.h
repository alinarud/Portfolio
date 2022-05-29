#ifndef PRINTERWIDGET_H
#define PRINTERWIDGET_H

#include <QWidget>

namespace Ui {
class PrinterWidget;
}

class PrinterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrinterWidget(QWidget *parent = nullptr);
    ~PrinterWidget();

private:
    Ui::PrinterWidget *m_ui;
};

#endif // PRINTERWIDGET_H
