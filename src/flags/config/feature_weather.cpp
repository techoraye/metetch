/**
 * Weather Display Toggle Feature
 * Allows users to enable/disable weather display
 */

#include <ncurses.h>
#include "data_types.h"

bool show_weather = true;

void toggleWeatherDisplay() {
    show_weather = !show_weather;
}

void displayWeatherToggleStatus(int row, int col) {
    mvprintw(row, col, "%s", (show_weather ? "ON" : "OFF"));
}

const char* getWeatherToggleLabel() {
    return "Show Weather Information";
}

bool isWeatherEnabled() {
    return show_weather;
}
