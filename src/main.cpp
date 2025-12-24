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
#include "flags.h"
#include "config_display.h"
#include "update_display.h"
#include "install_display.h"

using namespace std;
using namespace colors;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--config") == 0) {
            showConfigMenuHeader();
            showConfigMenu();
            return 0;
        } else if (strcmp(argv[1], "--update") == 0) {
            showUpdateCheckMessage();
            doUpdate();
            return 0;
        } else if (strcmp(argv[1], "--install") == 0) {
            showInstallStarting();
            doInstall();
            return 0;
        } else if (strcmp(argv[1], "--uninstall") == 0) {
            doUninstall();
            return 0;
        } else if (strcmp(argv[1], "--minimum") == 0 || strcmp(argv[1], "-m") == 0) {
            loadConfig();
            Info inf;
            collect(inf);
            renderMinimalDisplay(inf);
            return 0;
        } else if (strcmp(argv[1], "--full") == 0) {
            loadConfig();
            Info inf;
            collect(inf);
            renderDisplay(inf);
            return 0;
        } else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            showHelp();
            return 0;
        }
    }

    // Default behavior: show full display (no flag)
    loadConfig();
    Info inf;
    collect(inf);
    renderDisplay(inf);
    
    return 0;
}
