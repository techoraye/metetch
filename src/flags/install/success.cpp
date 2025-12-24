/**
 * Installation Success Display
 * Shows successful installation completion message
 */

#include <cstdio>
#include "colors.h"

using namespace colors;

void showInstallSuccess() {
    printf("\n");
    printf("%s┌──────────────────────────────────────────────────────────────┐%s\n", ACCENT_CYAN, RESET);
    printf("%s│%s                  %s✓ Installation Complete!%s                %s│%s\n", 
           ACCENT_CYAN, RESET, STATUS_OK, RESET, ACCENT_CYAN, RESET);
    printf("%s└──────────────────────────────────────────────────────────────┘%s\n\n", ACCENT_CYAN, RESET);
    
    printf("%sMetetch has been successfully installed!%s\n\n", TEXT_LABEL, RESET);
    
    printf("%sInstalled to:%s /usr/local/bin/metetch\n", TEXT_LABEL, RESET);
    printf("%sConfiguration:%s ~/.config/metetch/config.ini\n\n", TEXT_LABEL, RESET);
    
    printf("%sYou can now run:%s\n", TEXT_LABEL, RESET);
    printf("  %smetetch%s              Display system information\n", TEXT_VALUE, RESET);
    printf("  %smetetch --config%s     Configure preferences\n", TEXT_VALUE, RESET);
    printf("  %smetetch --help%s       Show help message\n\n", TEXT_VALUE, RESET);
    
    printf("%sMade with ❤️  by Techoraye%s\n\n", ACCENT_CYAN, RESET);
}
