/**
 * Update Installation Processor
 * Handles downloading and installing updates
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include "utils.h"

using namespace std;

extern string bin;
extern string repo;

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
