/**
 * Update Handler
 * Performs update check and installation
 */

#include <iostream>
#include "data_types.h"

using namespace std;

extern bool checkUpd();
extern void showInstallMessage();

void doUpdate() {
    cout << "Checking for updates...\n";
    if (!checkUpd()) {
        cout << "Already up to date!\n";
        return;
    }
    cout << "Update available. Use --install to install.\n";
}
