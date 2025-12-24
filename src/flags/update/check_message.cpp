/**
 * Update Check Message Display
 * Shows initial update checking message
 */

#include <iostream>
#include "colors.h"

using namespace std;
using namespace colors;

void showUpdateCheckMessage() {
    cout << "\n";
    cout << ACCENT_CYAN << "⚡ Checking for updates..." << RESET << "\n";
    cout << ACCENT_CYAN << "Please wait..." << RESET << "\n\n";
}
