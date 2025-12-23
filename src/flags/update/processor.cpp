/**
 * Update Processor
 * Performs update check
 */

#include <iostream>
#include "flags/update.h"

using namespace std;

extern bool checkUpd();

void doUpdate() {
    cout << "Checking for updates...\n";
    if (!checkUpd()) {
        cout << "Already up to date!\n";
        return;
    }
    cout << "Update available. Use --install to install.\n";
}
