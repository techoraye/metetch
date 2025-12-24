/**
 * Installation Executor
 * Downloads and installs the latest version
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include "utils.h"
#include "data_types.h"

using namespace std;

extern const string repo;
extern const string bin;

void doInstall() {
    cout << "Fetching latest version from " << repo << "\n";
    cout << "Downloading...\n";
    
    string tmpFile = "/tmp/metfetch_new";
    if (!downloadFile(bin, tmpFile)) {
        cout << "Download failed.\n";
        return;
    }
    cout << "Extracting...\n";
    
    string cmd = "chmod +x " + tmpFile;
    system(cmd.c_str());
    
    cout << "Installing...\n";
    cmd = "sudo mv " + tmpFile + " /usr/local/bin/metfetch";
    int ret = system(cmd.c_str());
    
    if (ret == 0) {
        cout << "\n✓ Installation successful!\n";
    } else {
        cout << "\n✗ Installation failed. Try: sudo mv " + tmpFile + " /usr/local/bin/metfetch\n";
    }
}
