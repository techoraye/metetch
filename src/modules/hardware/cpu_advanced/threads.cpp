/**
 * CPU Thread Count Detector
 * Retrieves the total number of CPU threads (logical processors)
 */

#include <string>
#include <cstdlib>
#include "modules/hardware/cpu_advanced.h"

namespace hardware::cpu_adv {

std::string executeCommand(const std::string& cmd);

// Get number of threads
int getThreadCount() {
    std::string output = executeCommand("lscpu | grep '^Thread(s)' | awk '{print $NF}'");
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
