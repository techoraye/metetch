/**
 * Current CPU Frequency Monitor
 * Retrieves the active CPU clock frequency
 */

#include <string>
#include <cstdlib>
#include "modules/hardware/cpu_advanced.h"

namespace hardware::cpu_adv {

std::string executeCommand(const std::string& cmd);

// Get current CPU frequency in MHz
float getCurrentFrequency() {
    std::string output = executeCommand("cat /proc/cpuinfo | grep 'cpu MHz' | head -1 | awk '{print $NF}'");
    if (!output.empty()) {
        try {
            return std::stof(output);
        } catch (...) {
            return 0.0f;
        }
    }
    return 0.0f;
}

} // namespace hardware::cpu_adv
