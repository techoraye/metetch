/**
 * System Resources Display Toggle Feature
 * Allows users to enable/disable system resource monitoring
 */

#include <ncurses.h>
#include "data_types.h"

bool show_system_resources = true;

void toggleSystemResources() {
    show_system_resources = !show_system_resources;
}

void displaySystemResourcesStatus(int row, int col) {
    mvprintw(row, col, "%s", (show_system_resources ? "ON" : "OFF"));
}

const char* getSystemResourcesLabel() {
    return "Show System Resources";
}

bool isSystemResourcesEnabled() {
    return show_system_resources;
}
