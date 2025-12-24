/**
 * Display Resolution Feature Toggle
 * Modular feature for display information
 */

#include "data_types.h"

extern Config cfg;

void toggleDisplayInfo() {
    cfg.show_display = !cfg.show_display;
}

bool getDisplayInfoStatus() {
    return cfg.show_display;
}

const char* getDisplayInfoLabel() {
    return "Display Information";
}

const char* getDisplayInfoDescription() {
    return "Show display resolution, refresh rate, and monitor information";
}
