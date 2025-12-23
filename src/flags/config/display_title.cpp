/**
 * Config Menu Display Title
 * Shows the configuration menu header and information
 */

#include <cstdio>

void showConfigMenuHeader() {
    printf("\n");
    printf("%s┌──────────────────────────────────────────────────────────────┐%s\n", "\x1b[36m", "\x1b[0m");
    printf("%s│%s                     %sMetetch Configuration%s                      %s│%s\n", 
           "\x1b[36m", "\x1b[0m", "\x1b[1m", "\x1b[0m", "\x1b[36m", "\x1b[0m");
    printf("%s└──────────────────────────────────────────────────────────────┘%s\n\n", "\x1b[36m", "\x1b[0m");
    
    printf("%sAvailable Options:%s\n", "\x1b[1m", "\x1b[0m");
    printf("  • Toggle display features (GPU, Disk, Network, Security, Weather)\n");
    printf("  • Control performance statistics visibility\n");
    printf("  • Show/hide system resources\n");
    printf("  • Customize color theme\n");
    printf("  • Save preferences to ~/.config/metetch/config.ini\n\n");
    
    printf("%sUse arrow keys to navigate, Space to toggle, Enter to select.%s\n", "\x1b[90m", "\x1b[0m");
    printf("%sPress ESC to cancel.%s\n\n", "\x1b[90m", "\x1b[0m");
}
