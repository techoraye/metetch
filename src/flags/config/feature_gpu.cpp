/**
 * GPU Display Toggle Feature
 * Allows users to enable/disable GPU monitoring display
 */

#include <ncurses.h>
#include "data_types.h"

void toggleGPUDisplay() {
    cfg.show_gpu = !cfg.show_gpu;
}

void displayGPUToggleStatus(int row, int col) {
    mvprintw(row, col, "%s", (cfg.show_gpu ? "ON" : "OFF"));
}

const char* getGPUToggleLabel() {
    return "Show GPU Information";
}
