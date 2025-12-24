/**
 * Extended Help Display
 * Shows detailed information including advanced configuration options
 */

#include <iostream>
#include "colors.h"

using namespace std;
using namespace colors;

extern void showHelp();

void showExtendedHelp() {
    showHelp();
    
    cout << TEXT_LABEL << "ADVANCED INFORMATION:" << RESET << "\n";
    cout << "  Configuration Location: ~/.config/metetch/config.ini\n";
    cout << "  Binary Location:        /usr/local/bin/metetch (after install)\n\n";
    
    cout << TEXT_LABEL << "CONFIGURATION OPTIONS:" << RESET << "\n";
    cout << "  Use 'metetch --config' to customize:\n";
    cout << "    - GPU monitoring display (on/off)\n";
    cout << "    - Disk usage display (on/off)\n";
    cout << "    - Real-time clock (on/off)\n";
    cout << "    - Color theme selection\n\n";
    
    cout << TEXT_LABEL << "DISPLAY INFORMATION:" << RESET << "\n";
    cout << "  Full mode displays:\n";
    cout << "    ├─ System Information (OS, kernel, uptime, user, shell, desktop)\n";
    cout << "    ├─ Hardware (CPU, memory, GPU, disk, battery, display)\n";
    cout << "    ├─ Network (hostname, IP address, interface, VPN)\n";
    cout << "    ├─ Security & Resources (CPU info, processes, threads)\n";
    cout << "    └─ Date & Time (current time, date, weather)\n\n";
    
    cout << "  Minimal mode displays (essential only):\n";
    cout << "    ├─ OS and kernel\n";
    cout << "    ├─ Uptime and user\n";
    cout << "    ├─ CPU, memory, and disk usage\n";
    cout << "    ├─ Hostname and IP address\n";
    cout << "    └─ GPU (if available)\n\n";
    
    cout << TEXT_LABEL << "FOR MORE INFORMATION:" << RESET << "\n";
    cout << "  Visit: https://github.com/techoraye/metetch\n";
    cout << "  Docs:  https://github.com/techoraye/metetch/blob/main/README.md\n\n";
}
