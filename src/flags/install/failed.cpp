/**
 * Installation Failure Display
 * Shows installation failure message with troubleshooting info
 */

#include <cstdio>
#include "colors.h"

using namespace colors;

void showInstallFailed(const char* reason) {
    printf("\n");
    printf("%s┌──────────────────────────────────────────────────────────────┐%s\n", ACCENT_CYAN, RESET);
    printf("%s│%s                  %s✗ Installation Failed%s                    %s│%s\n", 
           ACCENT_CYAN, RESET, STATUS_CRIT, RESET, ACCENT_CYAN, RESET);
    printf("%s└──────────────────────────────────────────────────────────────┘%s\n\n", ACCENT_CYAN, RESET);
    
    printf("%sInstallation failed!%s\n\n", STATUS_CRIT, RESET);
    
    if (reason) {
        printf("%sReason:%s %s\n\n", TEXT_LABEL, RESET, reason);
    }
    
    printf("%sTroubleshooting:%s\n", TEXT_LABEL, RESET);
    printf("  1. Check your internet connection\n");
    printf("  2. Try running: %ssudo ./install.sh%s from the project directory\n", TEXT_VALUE, RESET);
    printf("  3. Ensure you have administrator (sudo) access\n");
    printf("  4. Visit: %shttps://github.com/techoraye/metetch%s for help\n\n", ACCENT_CYAN, RESET);
    
    printf("%sMade with ❤️  by Techoraye%s\n\n", ACCENT_CYAN, RESET);
}
