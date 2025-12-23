#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "data_types.h"
#include "utils.h"

using namespace std;

bool checkUpd() {
    string remote = httpGet(api);
    if (remote.empty()) return false;
    string localVer = ver;
    return isNewer(remote, localVer);
}

void showInstallMessage() {
    cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
    cout << "║          ⚡ Metetch Update Available! ⚡              ║\n";
    cout << "║                                                           ║\n";
    cout << "║  Next steps:                                             ║\n";
    cout << "║    1. Run: " << "\x1b[1;33m" << "metetch" << "\x1b[0m" << "                                  ║\n";
    cout << "║    2. Configure: " << "\x1b[1;33m" << "metetch --config" << "\x1b[0m" << "              ║\n";
    cout << "║    3. Get help: " << "\x1b[1;33m" << "metetch --help" << "\x1b[0m" << "                ║\n";
    cout << "║                                                           ║\n";
    cout << "║  Binary location: /usr/local/bin/metetch                 ║\n";
    cout << "║  Config location: ~/.config/metetch/config.ini           ║\n";
    cout << "║                                                           ║\n";
    cout << "║  To uninstall: " << "\x1b[1;31m" << "sudo metetch --uninstall" << "\x1b[0m" << "          ║\n";
    cout << "╚═══════════════════════════════════════════════════════════╝\n\n";
}

void doUpdate() {
    cout << "Checking for updates...\n";
    if (!checkUpd()) {
        cout << "Already up to date!\n";
        return;
    }
    cout << "Update available. Use --install to install.\n";
}

void doInstall() {
    cout << "Fetching latest version from " << repo << "\n";
    al("Downloading...");
    
    string tmpFile = "/tmp/metfetch_new";
    if (!downloadFile(bin, tmpFile)) {
        cout << "Download failed.\n";
        return;
    }
    al("Extracting...");
    
    string cmd = "chmod +x " + tmpFile;
    system(cmd.c_str());
    
    al("Installing...");
    cmd = "sudo mv " + tmpFile + " /usr/local/bin/metfetch";
    int ret = system(cmd.c_str());
    
    if (ret == 0) {
        cout << "\n✓ Installation successful!\n";
    } else {
        cout << "\n✗ Installation failed. Try: sudo mv " + tmpFile + " /usr/local/bin/metfetch\n";
    }
}

