/**
 * Minimal Display Mode - Compact System Information
 * Displays essential system info in a compact format for users who prefer less text
 */

#include <cstdio>
#include <iomanip>
#include <cstring>
#include <string>
#include "data_types.h"
#include "colors.h"

using namespace std;
using namespace colors;

void renderMinimalDisplay(const Info& inf) {
    printf("\n");
    
    // Compact header
    printf("  %s⚡ Metetch System Info%s\n", ACCENT_CYAN, RESET);
    printf("  %s─────────────────────────────────────%s\n\n", ACCENT_CYAN, RESET);
    
    // Essential system info on single line format
    printf("  %sOS:%s %s  %s|  %sKernel:%s %s\n",
           TEXT_LABEL, RESET, inf.os.c_str(),
           ACCENT_CYAN,
           TEXT_LABEL, RESET, inf.kern.c_str());
    
    printf("  %sUptime:%s %s  %s|  %sUser:%s %s\n",
           TEXT_LABEL, RESET, inf.uptime.c_str(),
           ACCENT_CYAN,
           TEXT_LABEL, RESET, inf.user.c_str());
    
    // Hardware - single line format
    printf("  %sCPU:%s %.1f%%  %s|  %sMEM:%s %ld/%ldMB  %s|  %sDisk:%s %s\n",
           TEXT_LABEL, RESET, inf.cpu_load,
           ACCENT_CYAN,
           TEXT_LABEL, RESET, inf.mem_used, inf.mem_total,
           ACCENT_CYAN,
           TEXT_LABEL, RESET, inf.disk.c_str());
    
    // Network - single line format
    printf("  %sHostname:%s %s  %s|  %sIP:%s %s\n",
           TEXT_LABEL, RESET, inf.host.c_str(),
           ACCENT_CYAN,
           TEXT_LABEL, RESET, inf.ip.c_str());
    
    // Optional GPU if available
    if (inf.gpu != "Unknown GPU" && inf.gpu != "N/A") {
        printf("  %sGPU:%s %s\n",
               TEXT_LABEL, RESET, inf.gpu.c_str());
    }
    
    printf("\n  %s─────────────────────────────────────%s\n", ACCENT_CYAN, RESET);
    printf("  %s⚡ Made with ❤️  by Techoraye %s\n", ACCENT_CYAN, RESET);
    printf("  %s🔗 GitHub: https://github.com/techoraye/metetch %s\n\n", ACCENT_CYAN, RESET);
    
    fflush(stdout);
}
