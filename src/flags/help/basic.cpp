/**
 * Basic Help Display
 * Shows essential usage information and available commands
 */

#include <iostream>
#include "colors.h"

using namespace std;
using namespace colors;

void showHelp() {
    cout << "\n";
    cout << ACCENT_CYAN << "⚡ metetch - System Information Fetcher" << RESET << "\n\n";
    cout << "Usage: metetch [OPTION]\n\n";
    cout << TEXT_LABEL << "OPTIONS:" << RESET << "\n";
    cout << "  " << TEXT_LABEL << "(no option)" << RESET << "          Display minimal/compact information (default)\n";
    cout << "  " << TEXT_LABEL << "--full" << RESET << "               Show full system information\n";
    cout << "  " << TEXT_LABEL << "--minimum, -m" << RESET << "         Show minimal/compact information\n";
    cout << "  " << TEXT_LABEL << "--config" << RESET << "             Open interactive configuration menu\n";
    cout << "  " << TEXT_LABEL << "--update" << RESET << "             Check for available updates\n";
    cout << "  " << TEXT_LABEL << "--install" << RESET << "            Install latest available version\n";
    cout << "  " << TEXT_LABEL << "--uninstall" << RESET << "          Completely uninstall metetch\n";
    cout << "  " << TEXT_LABEL << "--help, -h" << RESET << "           Show this help message\n\n";
    
    cout << TEXT_LABEL << "EXAMPLES:" << RESET << "\n";
    cout << "  metetch                 Minimal/compact information (default)\n";
    cout << "  metetch --full          Full system information display (more details)\n";
    cout << "  metetch --minimum       Compact/minimal information\n";
    cout << "  metetch -m              Minimal mode (short form)\n";
    cout << "  metetch --config        Configure display preferences\n";
    cout << "  metetch --update        Check for updates\n";
    cout << "  metetch --help          Show this help message\n\n";
    
    cout << TEXT_LABEL << "DESCRIPTION:" << RESET << "\n";
    cout << "  Metetch is a beautiful system information display tool for Linux.\n";
    cout << "  It shows comprehensive system metrics in a modern, minimal design.\n\n";
    
    cout << TEXT_LABEL << "MODES:" << RESET << "\n";
    cout << "  Full Mode (--full) : Complete system information with all details\n";
    cout << "  Minimal Mode (-m)  : Essential information in compact format (default)\n\n";
    
    cout << ACCENT_CYAN << "Made with ❤️  by Techoraye" << RESET << "\n";
    cout << ACCENT_CYAN << "GitHub: https://github.com/techoraye/metetch" << RESET << "\n\n";
}
