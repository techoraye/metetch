/**
 * Uptime Display Feature Toggle
 * Modular feature for system uptime
 */

#include "data_types.h"

extern Config cfg;

void toggleUptimeDisplay() {
    cfg.show_uptime = !cfg.show_uptime;
}

bool getUptimeDisplayStatus() {
    return cfg.show_uptime;
}

const char* getUptimeDisplayLabel() {
    return "Uptime Display";
}

const char* getUptimeDisplayDescription() {
    return "Show system uptime and last boot information";
}
