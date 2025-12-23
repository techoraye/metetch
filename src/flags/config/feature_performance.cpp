/**
 * Performance Stats Display Toggle Feature
 * Allows users to enable/disable performance statistics
 */

#include <ncurses.h>
#include "data_types.h"

bool show_performance_stats = true;

void togglePerformanceStats() {
    show_performance_stats = !show_performance_stats;
}

void displayPerformanceStatsStatus(int row, int col) {
    mvprintw(row, col, "%s", (show_performance_stats ? "ON" : "OFF"));
}

const char* getPerformanceStatsLabel() {
    return "Show Performance Statistics";
}

bool isPerformanceStatsEnabled() {
    return show_performance_stats;
}
