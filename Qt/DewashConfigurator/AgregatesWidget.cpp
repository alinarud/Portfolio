#include "AgregatesWidget.h"
#include "ui_AgregatesWidget.h"
#include "DataManager.h"

//-------------------------------------------------------------------------------------------------
AgregatesWidget::AgregatesWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::AgregatesWidget)
{
    m_ui->setupUi(this);

    initMainBoardInputs();
    initMainBoardOutputs();
    initMainDispensers();
    initMainSensors();
    initExpansionBoardInputs();
    initExpansionBoardOutputs();
    initExpansionDispensers();
    initExpansionSensors();

    m_ui->le_expansion_modbus_addr->setText(DATA_MANAGER()->getExpensionBoardModbusAddress());
    m_ui->le_freq_converter1_modbus_addr->setText(DATA_MANAGER()->getExpensionBoardModbusAddress());
    m_ui->le_freq_converter2_modbus_addr->setText(DATA_MANAGER()->getExpensionBoardModbusAddress());
}
//-------------------------------------------------------------------------------------------------
AgregatesWidget::~AgregatesWidget()
{
    delete m_ui;
}
//-------------------------------------------------------------------------------------------------
void AgregatesWidget::initMainBoardInputs()
{
    QStringList lst;
    lst << tr("Option 1") << tr("Option 2") << tr("Option 3") << tr("Option 4") << tr("Option 5")
        << tr("Option 6") << tr("Option 7") << tr("Option 8") << tr("Option 9") << tr("Option 10")
        << tr("Option 11") << tr("Option 12") << tr("Option 13") << tr("Option 14") << tr("Option 15")
        << tr("Option 16") << tr("Option 17") << tr("Option 18") << tr("Option 19") << tr("Option 20")
        << tr("Bypass 1") << tr("Bypass 2") << tr("Car sensor");

    m_ui->cb_main_input_1->setProperty("index", 1);
    m_ui->cb_main_input_1->addItems(lst);
    m_ui->cb_main_input_1->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(1));

    m_ui->cb_main_input_2->setProperty("index", 2);
    m_ui->cb_main_input_2->addItems(lst);
    m_ui->cb_main_input_2->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(2));

    m_ui->cb_main_input_3->setProperty("index", 3);
    m_ui->cb_main_input_3->addItems(lst);
    m_ui->cb_main_input_3->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(3));

    m_ui->cb_main_input_4->setProperty("index", 4);
    m_ui->cb_main_input_4->addItems(lst);
    m_ui->cb_main_input_4->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(4));

    m_ui->cb_main_input_5->setProperty("index", 5);
    m_ui->cb_main_input_5->addItems(lst);
    m_ui->cb_main_input_5->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(5));

    m_ui->cb_main_input_6->setProperty("index", 6);
    m_ui->cb_main_input_6->addItems(lst);
    m_ui->cb_main_input_6->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(6));

    m_ui->cb_main_input_7->setProperty("index", 7);
    m_ui->cb_main_input_7->addItems(lst);
    m_ui->cb_main_input_7->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(7));

    m_ui->cb_main_input_8->setProperty("index", 8);
    m_ui->cb_main_input_8->addItems(lst);
    m_ui->cb_main_input_8->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(8));

    m_ui->cb_main_input_9->setProperty("index", 9);
    m_ui->cb_main_input_9->addItems(lst);
    m_ui->cb_main_input_9->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(9));

    m_ui->cb_main_input_10->setProperty("index", 10);
    m_ui->cb_main_input_10->addItems(lst);
    m_ui->cb_main_input_10->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(10));

    m_ui->cb_main_input_11->setProperty("index", 11);
    m_ui->cb_main_input_11->addItems(lst);
    m_ui->cb_main_input_11->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(11));

    m_ui->cb_main_input_12->setProperty("index", 12);
    m_ui->cb_main_input_12->addItems(lst);
    m_ui->cb_main_input_12->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(12));

    m_ui->cb_main_input_13->setProperty("index", 13);
    m_ui->cb_main_input_13->addItems(lst);
    m_ui->cb_main_input_13->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(13));

    m_ui->cb_main_input_14->setProperty("index", 14);
    m_ui->cb_main_input_14->addItems(lst);
    m_ui->cb_main_input_14->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(14));

    m_ui->cb_main_input_15->setProperty("index", 15);
    m_ui->cb_main_input_15->addItems(lst);
    m_ui->cb_main_input_15->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(15));

    m_ui->cb_main_input_16->setProperty("index", 16);
    m_ui->cb_main_input_16->addItems(lst);
    m_ui->cb_main_input_16->setCurrentIndex(DATA_MANAGER()->getMainBoardInputValue(16));
}
//-------------------------------------------------------------------------------------------------
void AgregatesWidget::initMainBoardOutputs()
{
    QStringList lst;
    // TODO: set output names

    m_ui->cb_main_output_1->setProperty("index", 1);
    m_ui->cb_main_output_1->addItems(lst);
    m_ui->cb_main_output_1->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(1));

    m_ui->cb_main_output_2->setProperty("index", 2);
    m_ui->cb_main_output_2->addItems(lst);
    m_ui->cb_main_output_2->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(2));

    m_ui->cb_main_output_3->setProperty("index", 3);
    m_ui->cb_main_output_3->addItems(lst);
    m_ui->cb_main_output_3->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(3));

    m_ui->cb_main_output_4->setProperty("index", 4);
    m_ui->cb_main_output_4->addItems(lst);
    m_ui->cb_main_output_4->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(4));

    m_ui->cb_main_output_5->setProperty("index", 5);
    m_ui->cb_main_output_5->addItems(lst);
    m_ui->cb_main_output_5->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(5));

    m_ui->cb_main_output_6->setProperty("index", 6);
    m_ui->cb_main_output_6->addItems(lst);
    m_ui->cb_main_output_6->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(6));

    m_ui->cb_main_output_7->setProperty("index", 7);
    m_ui->cb_main_output_7->addItems(lst);
    m_ui->cb_main_output_7->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(7));

    m_ui->cb_main_output_8->setProperty("index", 8);
    m_ui->cb_main_output_8->addItems(lst);
    m_ui->cb_main_output_8->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(8));

    m_ui->cb_main_output_9->setProperty("index", 9);
    m_ui->cb_main_output_9->addItems(lst);
    m_ui->cb_main_output_9->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(9));

    m_ui->cb_main_output_10->setProperty("index", 10);
    m_ui->cb_main_output_10->addItems(lst);
    m_ui->cb_main_output_10->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(10));

    m_ui->cb_main_output_11->setProperty("index", 11);
    m_ui->cb_main_output_11->addItems(lst);
    m_ui->cb_main_output_11->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(11));

    m_ui->cb_main_output_12->setProperty("index", 12);
    m_ui->cb_main_output_12->addItems(lst);
    m_ui->cb_main_output_12->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(12));

    m_ui->cb_main_output_13->setProperty("index", 13);
    m_ui->cb_main_output_13->addItems(lst);
    m_ui->cb_main_output_13->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(13));

    m_ui->cb_main_output_14->setProperty("index", 14);
    m_ui->cb_main_output_14->addItems(lst);
    m_ui->cb_main_output_14->setCurrentIndex(DATA_MANAGER()->getMainBoardOutputValue(14));
}
//-------------------------------------------------------------------------------------------------
void AgregatesWidget::initMainSensors()
{
    QStringList lst;
    lst << tr("Flow meter") << tr("Temperature sensor");

    m_ui->cb_main_sensor1_type->setProperty("index", 1);
    m_ui->cb_main_sensor1_type->addItems(lst);
    m_ui->cb_main_sensor1_type->setCurrentIndex(DATA_MANAGER()->getMainBoardSensorType(1));

    m_ui->sb_main_sensor1_pulses->setProperty("index", 1);
    m_ui->sb_main_sensor1_pulses->setValue(DATA_MANAGER()->getMainBoardSensorPulses(1));

    m_ui->cb_main_sensor2_type->setProperty("index", 2);
    m_ui->cb_main_sensor2_type->addItems(lst);
    m_ui->cb_main_sensor2_type->setCurrentIndex(DATA_MANAGER()->getMainBoardSensorType(2));

    m_ui->sb_main_sensor2_pulses->setProperty("index", 2);
    m_ui->sb_main_sensor2_pulses->setValue(DATA_MANAGER()->getMainBoardSensorPulses(2));

    m_ui->cb_main_sensor3_type->setProperty("index", 3);
    m_ui->cb_main_sensor3_type->addItems(lst);
    m_ui->cb_main_sensor3_type->setCurrentIndex(DATA_MANAGER()->getMainBoardSensorType(3));

    m_ui->sb_main_sensor3_pulses->setProperty("index", 3);
    m_ui->sb_main_sensor3_pulses->setValue(DATA_MANAGER()->getMainBoardSensorPulses(3));

    m_ui->cb_main_sensor4_type->setProperty("index", 4);
    m_ui->cb_main_sensor4_type->addItems(lst);
    m_ui->cb_main_sensor4_type->setCurrentIndex(DATA_MANAGER()->getMainBoardSensorType(4));

    m_ui->sb_main_sensor4_pulses->setProperty("index", 4);
    m_ui->sb_main_sensor4_pulses->setValue(DATA_MANAGER()->getMainBoardSensorPulses(4));
}
//-------------------------------------------------------------------------------------------------
void AgregatesWidget::initMainDispensers()
{
    m_ui->sb_main_dispenser1_freq->setProperty("index", 1);
    m_ui->sb_main_dispenser1_filling->setProperty("index", 1);
    m_ui->sb_main_dispenser1_freq->setValue(DATA_MANAGER()->getMainBoardDispenserFrequency(1));
    m_ui->sb_main_dispenser1_filling->setValue(DATA_MANAGER()->getMainBoardDispenserFilling(1));

    m_ui->sb_main_dispenser2_freq->setProperty("index", 2);
    m_ui->sb_main_dispenser2_filling->setProperty("index", 2);
    m_ui->sb_main_dispenser2_freq->setValue(DATA_MANAGER()->getMainBoardDispenserFrequency(2));
    m_ui->sb_main_dispenser2_filling->setValue(DATA_MANAGER()->getMainBoardDispenserFilling(2));

    m_ui->sb_main_dispenser3_freq->setProperty("index", 3);
    m_ui->sb_main_dispenser3_filling->setProperty("index", 3);
    m_ui->sb_main_dispenser3_freq->setValue(DATA_MANAGER()->getMainBoardDispenserFrequency(3));
    m_ui->sb_main_dispenser3_filling->setValue(DATA_MANAGER()->getMainBoardDispenserFilling(3));

    m_ui->sb_main_dispenser4_freq->setProperty("index", 4);
    m_ui->sb_main_dispenser4_filling->setProperty("index", 4);
    m_ui->sb_main_dispenser4_freq->setValue(DATA_MANAGER()->getMainBoardDispenserFrequency(4));
    m_ui->sb_main_dispenser4_filling->setValue(DATA_MANAGER()->getMainBoardDispenserFilling(4));

}
//-------------------------------------------------------------------------------------------------
void AgregatesWidget::initExpansionBoardInputs()
{
    QStringList lst;
    lst << tr("Bypass 1") << tr("Bypass 2") << tr("Car sensor");

    m_ui->cb_expansion_input_1->setProperty("index", 1);
    m_ui->cb_expansion_input_1->addItems(lst);
    m_ui->cb_expansion_input_1->setCurrentIndex(DATA_MANAGER()->getExpensionBoardInputValue(1));

    m_ui->cb_expansion_input_2->setProperty("index", 2);
    m_ui->cb_expansion_input_2->addItems(lst);
    m_ui->cb_expansion_input_2->setCurrentIndex(DATA_MANAGER()->getExpensionBoardInputValue(2));

    m_ui->cb_expansion_input_3->setProperty("index", 3);
    m_ui->cb_expansion_input_3->addItems(lst);
    m_ui->cb_expansion_input_3->setCurrentIndex(DATA_MANAGER()->getExpensionBoardInputValue(3));

    m_ui->cb_expansion_input_4->setProperty("index", 4);
    m_ui->cb_expansion_input_4->addItems(lst);
    m_ui->cb_expansion_input_4->setCurrentIndex(DATA_MANAGER()->getExpensionBoardInputValue(4));

    m_ui->cb_expansion_input_5->setProperty("index", 5);
    m_ui->cb_expansion_input_5->addItems(lst);
    m_ui->cb_expansion_input_5->setCurrentIndex(DATA_MANAGER()->getExpensionBoardInputValue(5));

    m_ui->cb_expansion_input_6->setProperty("index", 6);
    m_ui->cb_expansion_input_6->addItems(lst);
    m_ui->cb_expansion_input_6->setCurrentIndex(DATA_MANAGER()->getExpensionBoardInputValue(6));

    m_ui->cb_expansion_input_7->setProperty("index", 7);
    m_ui->cb_expansion_input_7->addItems(lst);
    m_ui->cb_expansion_input_7->setCurrentIndex(DATA_MANAGER()->getExpensionBoardInputValue(7));

    m_ui->cb_expansion_input_8->setProperty("index", 8);
    m_ui->cb_expansion_input_8->addItems(lst);
    m_ui->cb_expansion_input_8->setCurrentIndex(DATA_MANAGER()->getExpensionBoardInputValue(8));
}
//-------------------------------------------------------------------------------------------------
void AgregatesWidget::initExpansionBoardOutputs()
{
    QStringList lst;
    // TODO: set output names

    m_ui->cb_expansion_output_1->setProperty("index", 1);
    m_ui->cb_expansion_output_1->addItems(lst);
    m_ui->cb_expansion_output_1->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(1));

    m_ui->cb_expansion_output_2->setProperty("index", 2);
    m_ui->cb_expansion_output_2->addItems(lst);
    m_ui->cb_expansion_output_2->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(2));

    m_ui->cb_expansion_output_3->setProperty("index", 3);
    m_ui->cb_expansion_output_3->addItems(lst);
    m_ui->cb_expansion_output_3->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(3));

    m_ui->cb_expansion_output_4->setProperty("index", 4);
    m_ui->cb_expansion_output_4->addItems(lst);
    m_ui->cb_expansion_output_4->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(4));

    m_ui->cb_expansion_output_5->setProperty("index", 5);
    m_ui->cb_expansion_output_5->addItems(lst);
    m_ui->cb_expansion_output_5->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(5));

    m_ui->cb_expansion_output_6->setProperty("index", 6);
    m_ui->cb_expansion_output_6->addItems(lst);
    m_ui->cb_expansion_output_6->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(6));

    m_ui->cb_expansion_output_7->setProperty("index", 7);
    m_ui->cb_expansion_output_7->addItems(lst);
    m_ui->cb_expansion_output_7->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(7));

    m_ui->cb_expansion_output_8->setProperty("index", 8);
    m_ui->cb_expansion_output_8->addItems(lst);
    m_ui->cb_expansion_output_8->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(8));

    m_ui->cb_expansion_output_9->setProperty("index", 9);
    m_ui->cb_expansion_output_9->addItems(lst);
    m_ui->cb_expansion_output_9->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(9));

    m_ui->cb_expansion_output_10->setProperty("index", 10);
    m_ui->cb_expansion_output_10->addItems(lst);
    m_ui->cb_expansion_output_10->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(10));

    m_ui->cb_expansion_output_11->setProperty("index", 11);
    m_ui->cb_expansion_output_11->addItems(lst);
    m_ui->cb_expansion_output_11->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(11));

    m_ui->cb_expansion_output_12->setProperty("index", 12);
    m_ui->cb_expansion_output_12->addItems(lst);
    m_ui->cb_expansion_output_12->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(12));

    m_ui->cb_expansion_output_13->setProperty("index", 13);
    m_ui->cb_expansion_output_13->addItems(lst);
    m_ui->cb_expansion_output_13->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(13));

    m_ui->cb_expansion_output_14->setProperty("index", 14);
    m_ui->cb_expansion_output_14->addItems(lst);
    m_ui->cb_expansion_output_14->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(14));

    m_ui->cb_expansion_output_15->setProperty("index", 15);
    m_ui->cb_expansion_output_15->addItems(lst);
    m_ui->cb_expansion_output_15->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(1));

    m_ui->cb_expansion_output_16->setProperty("index", 16);
    m_ui->cb_expansion_output_16->addItems(lst);
    m_ui->cb_expansion_output_16->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(2));

    m_ui->cb_expansion_output_17->setProperty("index", 17);
    m_ui->cb_expansion_output_17->addItems(lst);
    m_ui->cb_expansion_output_17->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(3));

    m_ui->cb_expansion_output_18->setProperty("index", 18);
    m_ui->cb_expansion_output_18->addItems(lst);
    m_ui->cb_expansion_output_18->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(4));

    m_ui->cb_expansion_output_19->setProperty("index", 19);
    m_ui->cb_expansion_output_19->addItems(lst);
    m_ui->cb_expansion_output_19->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(5));

    m_ui->cb_expansion_output_20->setProperty("index", 20);
    m_ui->cb_expansion_output_20->addItems(lst);
    m_ui->cb_expansion_output_20->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(6));

    m_ui->cb_expansion_output_21->setProperty("index", 21);
    m_ui->cb_expansion_output_21->addItems(lst);
    m_ui->cb_expansion_output_21->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(7));

    m_ui->cb_expansion_output_22->setProperty("index", 22);
    m_ui->cb_expansion_output_22->addItems(lst);
    m_ui->cb_expansion_output_22->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(8));

    m_ui->cb_expansion_output_23->setProperty("index", 23);
    m_ui->cb_expansion_output_23->addItems(lst);
    m_ui->cb_expansion_output_23->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(9));

    m_ui->cb_expansion_output_24->setProperty("index", 24);
    m_ui->cb_expansion_output_24->addItems(lst);
    m_ui->cb_expansion_output_24->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(10));

    m_ui->cb_expansion_output_25->setProperty("index", 25);
    m_ui->cb_expansion_output_25->addItems(lst);
    m_ui->cb_expansion_output_25->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(11));

    m_ui->cb_expansion_output_26->setProperty("index", 26);
    m_ui->cb_expansion_output_26->addItems(lst);
    m_ui->cb_expansion_output_26->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(12));

    m_ui->cb_expansion_output_27->setProperty("index", 27);
    m_ui->cb_expansion_output_27->addItems(lst);
    m_ui->cb_expansion_output_27->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(13));

    m_ui->cb_expansion_output_28->setProperty("index", 28);
    m_ui->cb_expansion_output_28->addItems(lst);
    m_ui->cb_expansion_output_28->setCurrentIndex(DATA_MANAGER()->getExpensionBoardOutputValue(14));
}
//-------------------------------------------------------------------------------------------------
void AgregatesWidget::initExpansionSensors()
{
    QStringList lst;
    lst << tr("Flow meter") << tr("Temperature sensor");

    m_ui->cb_expansion_sensor1_type->setProperty("index", 1);
    m_ui->cb_expansion_sensor1_type->addItems(lst);
    m_ui->cb_expansion_sensor1_type->setCurrentIndex(DATA_MANAGER()->getExpensionBoardSensorType(1));

    m_ui->sb_expansion_sensor1_pulses->setProperty("index", 1);
    m_ui->sb_expansion_sensor1_pulses->setValue(DATA_MANAGER()->getExpensionBoardSensorPulses(1));

    m_ui->cb_expansion_sensor2_type->setProperty("index", 2);
    m_ui->cb_expansion_sensor2_type->addItems(lst);
    m_ui->cb_expansion_sensor2_type->setCurrentIndex(DATA_MANAGER()->getExpensionBoardSensorType(2));

    m_ui->sb_expansion_sensor2_pulses->setProperty("index", 2);
    m_ui->sb_expansion_sensor2_pulses->setValue(DATA_MANAGER()->getExpensionBoardSensorPulses(2));

    m_ui->cb_expansion_sensor3_type->setProperty("index", 3);
    m_ui->cb_expansion_sensor3_type->addItems(lst);
    m_ui->cb_expansion_sensor3_type->setCurrentIndex(DATA_MANAGER()->getExpensionBoardSensorType(3));

    m_ui->sb_expansion_sensor3_pulses->setProperty("index", 3);
    m_ui->sb_expansion_sensor3_pulses->setValue(DATA_MANAGER()->getExpensionBoardSensorPulses(3));

    m_ui->cb_expansion_sensor4_type->setProperty("index", 4);
    m_ui->cb_expansion_sensor4_type->addItems(lst);
    m_ui->cb_expansion_sensor4_type->setCurrentIndex(DATA_MANAGER()->getExpensionBoardSensorType(4));

    m_ui->sb_expansion_sensor4_pulses->setProperty("index", 4);
    m_ui->sb_expansion_sensor4_pulses->setValue(DATA_MANAGER()->getExpensionBoardSensorPulses(4));
}
//-------------------------------------------------------------------------------------------------
void AgregatesWidget::initExpansionDispensers()
{
    m_ui->sb_expansion_dispenser1_freq->setProperty("index", 1);
    m_ui->sb_expansion_dispenser1_filling->setProperty("index", 1);
    m_ui->sb_expansion_dispenser1_freq->setValue(DATA_MANAGER()->getExpensionBoardDispenserFrequency(1));
    m_ui->sb_expansion_dispenser1_filling->setValue(DATA_MANAGER()->getExpensionBoardDispenserFilling(1));

    m_ui->sb_expansion_dispenser2_freq->setProperty("index", 2);
    m_ui->sb_expansion_dispenser2_filling->setProperty("index", 2);
    m_ui->sb_expansion_dispenser2_freq->setValue(DATA_MANAGER()->getExpensionBoardDispenserFrequency(2));
    m_ui->sb_expansion_dispenser2_filling->setValue(DATA_MANAGER()->getExpensionBoardDispenserFilling(2));

    m_ui->sb_expansion_dispenser3_freq->setProperty("index", 3);
    m_ui->sb_expansion_dispenser3_filling->setProperty("index", 3);
    m_ui->sb_expansion_dispenser3_freq->setValue(DATA_MANAGER()->getExpensionBoardDispenserFrequency(3));
    m_ui->sb_expansion_dispenser3_filling->setValue(DATA_MANAGER()->getExpensionBoardDispenserFilling(3));

    m_ui->sb_expansion_dispenser4_freq->setProperty("index", 4);
    m_ui->sb_expansion_dispenser4_filling->setProperty("index", 4);
    m_ui->sb_expansion_dispenser4_freq->setValue(DATA_MANAGER()->getExpensionBoardDispenserFrequency(4));
    m_ui->sb_expansion_dispenser4_filling->setValue(DATA_MANAGER()->getExpensionBoardDispenserFilling(4));

}
//-------------------------------------------------------------------------------------------------
void AgregatesWidget::onMainBoardInputIndexChanged(int currentIndex)
{

}
//-------------------------------------------------------------------------------------------------
