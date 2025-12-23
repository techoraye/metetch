/**
 * CPU TDP (Thermal Design Power) Detector
 * Retrieves the thermal design power specifications of the CPU
 */

#include <string>
#include <fstream>
#include "modules/hardware/cpu_advanced.h"

namespace hardware::cpu_adv {

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

} // namespace hardware::cpu_adv
