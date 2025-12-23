/**
 * Network Display Toggle Feature
 * Allows users to enable/disable advanced network monitoring
 */

#include <ncurses.h>
#include "data_types.h"

bool show_network_advanced = true;

void toggleNetworkDisplay() {
    show_network_advanced = !show_network_advanced;
}

void displayNetworkToggleStatus(int row, int col) {
    mvprintw(row, col, "%s", (show_network_advanced ? "ON" : "OFF"));
}

const char* getNetworkToggleLabel() {
    return "Show Advanced Network Info";
}

bool isNetworkAdvancedEnabled() {
    return show_network_advanced;
}
