/**
 * Installation Starting Display
 * Shows the initial installation message
 */

#include <cstdio>
#include "colors.h"

using namespace colors;

void showInstallStarting() {
    printf("\n");
    printf("%s┌──────────────────────────────────────────────────────────────┐%s\n", ACCENT_CYAN, RESET);
    printf("%s│%s                   %sInstalling Metetch%s                       %s│%s\n", 
           ACCENT_CYAN, RESET, TEXT_LABEL, RESET, ACCENT_CYAN, RESET);
    printf("%s└──────────────────────────────────────────────────────────────┘%s\n\n", ACCENT_CYAN, RESET);
    
    printf("%sStarting installation process...%s\n", TEXT_MUTED, RESET);
}
