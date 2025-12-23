/**
 * Disk Display Toggle Feature
 * Allows users to enable/disable disk monitoring display
 */

#include <ncurses.h>
#include "data_types.h"

void toggleDiskDisplay() {
    cfg.show_disk = !cfg.show_disk;
}

void displayDiskToggleStatus(int row, int col) {
    mvprintw(row, col, "%s", (cfg.show_disk ? "ON" : "OFF"));
}

const char* getDiskToggleLabel() {
    return "Show Disk Information";
}
