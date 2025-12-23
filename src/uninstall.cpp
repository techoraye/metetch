#include <iostream>
#include <string>
#include <cstdlib>
#include "data_types.h"
#include "utils.h"

using namespace std;

void doUninstall() {
    cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
    cout << "║         ⚠️  Complete Uninstall - Remove All Traces       ║\n";
    cout << "╚═══════════════════════════════════════════════════════════╝\n\n";
    cout << "This will remove:\n";
    cout << "  ✓ Binary: /usr/local/bin/metetch\n";
    cout << "  ✓ Config: ~/.config/metetch/\n";
    cout << "  ✓ All configuration files\n\n";
    
    cout << "Are you sure? (yes/no): ";
    string confirm;
    getline(cin, confirm);
    
    if (confirm != "yes" && confirm != "YES") {
        cout << "Uninstall cancelled.\n";
        return;
    }
    
    cout << "\n";
    al("Removing...");
    
    // Remove binary
    system("sudo rm -f /usr/local/bin/metetch 2>/dev/null");
    
    // Remove config directory
    system("rm -rf ~/.config/metetch 2>/dev/null");
    
    // Also try removing from /usr/bin if it exists
    system("sudo rm -f /usr/bin/metetch 2>/dev/null");
    
    cout << "\n✓ Uninstall complete! All traces removed.\n";
    cout << "\nMetetch has been completely uninstalled.\n\n";
}
