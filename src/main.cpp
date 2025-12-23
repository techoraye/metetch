/*
 * Metetch - System Information Fetcher
 * Copyright (c) 2025 techoraye - All Rights Reserved
 * Licensed under METETCH PROPRIETARY LICENSE
 * This software and source code are proprietary and confidential
 * See LICENSE file for details
 */

#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>
#include "data_types.h"
#include "colors.h"
#include "utils.h"
#include "uninstall.h"

using namespace std;
using namespace colors;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--config") == 0) {
            configureMenu();
            return 0;
        } else if (strcmp(argv[1], "--update") == 0) {
            doUpdate();
            return 0;
        } else if (strcmp(argv[1], "--install") == 0) {
            doInstall();
            return 0;
        } else if (strcmp(argv[1], "--uninstall") == 0) {
            doUninstall();
            return 0;
        } else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            cout << "metetch - System Information Fetcher\n\n";
            cout << "Usage: metetch [OPTION]\n\n";
            cout << "Options:\n";
            cout << "  --config        Open configuration menu\n";
            cout << "  --update        Check for updates\n";
            cout << "  --install       Install latest version\n";
            cout << "  --uninstall     Completely uninstall (removes all traces)\n";
            cout << "  --help, -h      Show this help message\n";
            cout << "\nWithout options, displays system information.\n";
            return 0;
        }
    }

    loadConfig();
    Info inf;
    collect(inf);
    renderDisplay(inf);
    
    // Static display mode - no live refresh, allows scrolling
    thread checkUpdateThread([]() {
        this_thread::sleep_for(chrono::seconds(5));
        if (checkUpd() && !lv.update_shown.exchange(true)) {
            showInstallMessage();
        }
    });
    checkUpdateThread.detach();

    return 0;
}
