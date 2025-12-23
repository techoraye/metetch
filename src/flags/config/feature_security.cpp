/**
 * Security Information Display Toggle Feature
 * Allows users to enable/disable security monitoring display
 */

#include <ncurses.h>
#include "data_types.h"

bool show_security_info = true;

void toggleSecurityDisplay() {
    show_security_info = !show_security_info;
}

void displaySecurityToggleStatus(int row, int col) {
    mvprintw(row, col, "%s", (show_security_info ? "ON" : "OFF"));
}

const char* getSecurityToggleLabel() {
    return "Show Security Information";
}

bool isSecurityInfoEnabled() {
    return show_security_info;
}
