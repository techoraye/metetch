/**
 * Theme Selection Feature
 * Allows users to customize color theme
 */

#include <ncurses.h>
#include <string>
#include "data_types.h"

using namespace std;

void selectTheme() {
    echo();
    curs_set(1);
    mvprintw(12, 4, "Enter theme (default/dark/light): ");
    char buf[128] = {0};
    getnstr(buf, sizeof(buf)-1);
    if (buf[0]) cfg.theme = string(buf);
    noecho();
    curs_set(0);
}

void displayThemeStatus(int row, int col) {
    mvprintw(row, col, "%s", cfg.theme.c_str());
}

const char* getThemeLabel() {
    return "Select Color Theme";
}

string getCurrentTheme() {
    return cfg.theme;
}
