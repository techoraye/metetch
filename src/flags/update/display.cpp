/**
 * Update Display Message
 * Shows update availability message
 */

#include <iostream>

using namespace std;

void showInstallMessage() {
    cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
    cout << "║          ⚡ Metetch Update Available! ⚡              ║\n";
    cout << "║                                                           ║\n";
    cout << "║  Made with ❤️  | https://github.com/techoraye/metetch   ║\n";
    cout << "║                                                           ║\n";
    cout << "║  To update, run:                                         ║\n";
    cout << "║    " << "\x1b[1;33m" << "sudo metetch --install" << "\x1b[0m" << "                         ║\n";
    cout << "║                                                           ║\n";
    cout << "║  Or update via your package manager                      ║\n";
    cout << "╚═══════════════════════════════════════════════════════════╝\n\n";
}
