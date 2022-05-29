#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

namespace TagName {
    const QString TAG_SETTINGS = "SETTINGS";
    const QString TAG_MAIN_BOARD = "MAIN_BOARD";
    const QString TAG_EXPENSION_BOARD = "EXPENSION_BOARD";
    const QString TAG_INPUTS = "INPUTS";
    const QString TAG_INPUT = "INPUT";
    const QString TAG_OUTPUTS = "OUTPUTS";
    const QString TAG_OUTPUT = "OUTPUT";
    const QString TAG_SENSORS = "SENSORS";
    const QString TAG_SENSOR = "SENSOR";
    const QString TAG_DISPENSERS = "DISPENSERS";
    const QString TAG_DISPENSER = "DISPENSER";
    const QString TAG_FREQUENCY_CONVERTERS = "FREQUENCY_CONVERTERS";
    const QString TAG_FREQUENCY_CONVERTER = "FREQUENCY_CONVERTER";
}

namespace AttributeNames {
    const QString INDEX = "index";
    const QString VALUE = "value";
    const QString FREQUENCY = "frequency";
    const QString FILLING = "filling";
    const QString TYPE = "type";
    const QString PULSES = "pulses";
    const QString ENABLE = "enable";
    const QString MODBUS_ADDRESS = "modbus_address";
}

#endif // CONSTANTS_H
