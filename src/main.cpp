/*
 * Metetch - System Information Fetcher
 *
 * Copyright (c) 2025 techoraye
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
