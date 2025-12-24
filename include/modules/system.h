#pragma once

#include <string>

namespace sys {
    std::string getUser();
    std::string getHostname();
    std::string getOS();
    std::string getKernel();
    std::string getUptime();
    std::string getShell();
    std::string getTerminal();
    std::string getDesktopEnvironment();
    std::string getWindowManager();
    int getPackageCount();
    int getEmergePackageCount();
    int getFlatpakPackageCount();
    int getProcessCount();
    int getThreadCount();
}
