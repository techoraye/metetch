/**
 * Battery Display Feature Toggle
 * Modular feature for battery information
 */

#include "data_types.h"

extern Config cfg;

void toggleBatteryDisplay() {
    cfg.show_battery = !cfg.show_battery;
}

bool getBatteryDisplayStatus() {
    return cfg.show_battery;
}

const char* getBatteryDisplayLabel() {
    return "Battery Display";
}

const char* getBatteryDisplayDescription() {
    return "Show battery status, charge level, and power information";
}
