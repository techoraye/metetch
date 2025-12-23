/**
 * Installation Progress Display
 * Shows installation progress steps
 */

#include <cstdio>
#include "colors.h"

using namespace colors;

void showInstallProgress(const char* step) {
    printf("  %s→%s %s\n", ACCENT_CYAN, RESET, step);
}
