/**
 * System Module: Operating System
 * Retrieves OS information from /etc/os-release
 */

#include <string>
#include <fstream>
#include <sstream>
#include "modules/system/os.h"

namespace system::os {

std::string get() {
    std::ifstream file("/etc/os-release");
    if (!file.is_open()) return "Unknown";
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("PRETTY_NAME=") == 0) {
            size_t start = line.find('"') + 1;
            size_t end = line.rfind('"');
            if (start > 0 && end != std::string::npos && start < end) {
                return line.substr(start, end - start);
            }
        }
    }
    return "Unknown";
}

} // namespace system::os
