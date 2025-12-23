/**
 * Hardware Module: Advanced CPU
 * Retrieves detailed CPU frequency, power, and per-core information
 */

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "modules/hardware/cpu_advanced.h"

namespace hardware::cpu_adv {

// Helper to execute commands
std::string executeCommand(const std::string& cmd) {
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";
    
    std::string result;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

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

// Get CPU TDP (from /proc/cpuinfo or estimation)
float getTDP() {
    // Try to read from /proc/cpuinfo
    std::ifstream cpuinfo("/proc/cpuinfo");
    if (cpuinfo.is_open()) {
        std::string line;
        while (std::getline(cpuinfo, line)) {
            if (line.find("power management") != std::string::npos) {
                return 65.0f; // Default conservative estimate
            }
        }
    }
    
    // Return conservative estimate based on architecture
    return 65.0f;
}

// Get current CPU power draw (requires special tools)
float getCPUPowerDraw() {
    // Try turbostat
    std::string output = executeCommand("turbostat --quiet --interval 1 --num_iterations 1 2>/dev/null | grep Package | head -1 | awk '{print $NF}'");
    if (!output.empty() && output.find("W") != std::string::npos) {
        try {
            std::string num = output.substr(0, output.find("W"));
            return std::stof(num);
        } catch (...) {
            return 0.0f;
        }
    }
    
    // Try RAPL (Running Average Power Limit)
    output = executeCommand("cat /sys/class/powercap/intel-rapl/intel-rapl:0/energy_uj 2>/dev/null");
    if (!output.empty()) {
        // This gives energy in microjoules, can't directly convert to power without timestamps
        return 0.0f;
    }
    
    return 0.0f;
}

// Get detailed CPU info
CPUAdvancedInfo getCPUAdvancedInfo() {
    CPUAdvancedInfo info;
    info.current_frequency = getCurrentFrequency();
    info.max_frequency = getMaxFrequency();
    info.base_frequency = getBaseFrequency();
    info.core_count = getCoreCount();
    info.thread_count = getThreadCount();
    info.thermal_design_power = getTDP();
    info.current_power_draw = getCPUPowerDraw();
    
    return info;
}

} // namespace hardware::cpu_adv
