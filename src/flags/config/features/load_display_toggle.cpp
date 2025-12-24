/**
 * CPU Load Display Feature Toggle
 * Modular feature for CPU load metrics
 */

#include "data_types.h"

extern Config cfg;

void toggleLoadDisplay() {
    cfg.show_load = !cfg.show_load;
}

bool getLoadDisplayStatus() {
    return cfg.show_load;
}

const char* getLoadDisplayLabel() {
    return "CPU Load Display";
}

const char* getLoadDisplayDescription() {
    return "Show CPU load, temperature, and performance metrics";
}
