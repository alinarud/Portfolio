#ifndef AGREGATESWIDGET_H
#define AGREGATESWIDGET_H

#include <QWidget>

namespace Ui {
class AgregatesWidget;
}

class AgregatesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AgregatesWidget(QWidget *parent = nullptr);
    ~AgregatesWidget();

private:
    void initMainBoardInputs();
    void initMainBoardOutputs();
    void initMainSensors();
    void initMainDispensers();
    void initExpansionBoardInputs();
    void initExpansionBoardOutputs();
    void initExpansionSensors();
    void initExpansionDispensers();

private slots:
    void onMainBoardInputIndexChanged(int currentIndex);

private:
    Ui::AgregatesWidget *m_ui;
};

#endif // AGREGATESWIDGET_H
