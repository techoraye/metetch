/**
 * Base CPU Frequency Detector
 * Determines the base CPU frequency from system information
 */

#include <string>
#include <cstdlib>
#include "modules/hardware/cpu_advanced.h"

namespace hardware::cpu_adv {

std::string executeCommand(const std::string& cmd);

// Get base CPU frequency (from cpuinfo)
float getBaseFrequency() {
    std::string output = executeCommand("lscpu | grep 'CPU min MHz' | awk '{print $NF}'");
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
