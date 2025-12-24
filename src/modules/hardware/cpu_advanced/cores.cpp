/**
 * CPU Core Count Detector
 * Retrieves the number of physical CPU cores
 */

#include <string>
#include <cstdlib>
#include "modules/hardware/cpu_advanced.h"

namespace hardware::cpu_adv {

std::string executeCommand(const std::string& cmd);

// Get number of physical cores
int getCoreCount() {
    std::string output = executeCommand("lscpu | grep '^Core(s)' | awk '{print $NF}'");
    if (!output.empty()) {
        try {
            return std::stoi(output);
        } catch (...) {
            return 1;
        }
    }
    return 1;
}

} // namespace hardware::cpu_adv
