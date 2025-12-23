/**
 * Battery Display Toggle Feature
 * Enable/disable battery information (for laptops)
 */

#include "data_types.h"

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
    return "Show battery status and percentage (laptops)";
}
