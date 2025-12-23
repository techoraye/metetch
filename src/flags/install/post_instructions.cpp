/**
 * Post-Installation Instructions Display
 * Shows next steps after successful installation
 */

#include <cstdio>
#include "colors.h"

using namespace colors;

void showPostInstallInstructions() {
    printf("\n");
    printf("%s┌──────────────────────────────────────────────────────────────┐%s\n", ACCENT_CYAN, RESET);
    printf("%s│%s                  %sNext Steps%s                                %s│%s\n", 
           ACCENT_CYAN, RESET, TEXT_LABEL, RESET, ACCENT_CYAN, RESET);
    printf("%s└──────────────────────────────────────────────────────────────┘%s\n\n", ACCENT_CYAN, RESET);
    
    printf("%sOptional Setup:%s\n", TEXT_LABEL, RESET);
    printf("  1. Configure preferences: %smetetch --config%s\n", TEXT_VALUE, RESET);
    printf("  2. View full help:       %smetetch --help%s\n", TEXT_VALUE, RESET);
    printf("  3. Read documentation:   https://github.com/techoraye/metetch\n\n");
    
    printf("%sSystem Integration:%s\n", TEXT_LABEL, RESET);
    printf("  • Binary location: /usr/local/bin/metetch\n");
    printf("  • Config location: ~/.config/metetch/config.ini\n");
    printf("  • Available globally as 'metetch' command\n\n");
    
    printf("%sMade with ❤️  by Techoraye%s\n\n", ACCENT_CYAN, RESET);
}
