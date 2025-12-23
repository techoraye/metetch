/**
 * Maximum CPU Frequency Detector
 * Determines the maximum CPU frequency supported by the system
 */

#include <string>
#include <fstream>
#include <cstdlib>
#include "modules/hardware/cpu_advanced.h"

namespace hardware::cpu_adv {

std::string executeCommand(const std::string& cmd);

// Get max CPU frequency in MHz
float getMaxFrequency() {
    // Try to read from sys/devices/system/cpu
    std::ifstream max_freq("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq");
    if (max_freq.is_open()) {
        std::string line;
        std::getline(max_freq, line);
        try {
            return std::stof(line) / 1000.0f; // Convert from kHz to MHz
        } catch (...) {
            return 0.0f;
        }
    }
    
    // Fallback: estimate from cpuinfo
    std::string output = executeCommand("lscpu | grep 'CPU max MHz' | awk '{print $NF}'");
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
