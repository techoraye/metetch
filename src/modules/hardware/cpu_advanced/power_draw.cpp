/**
 * CPU Power Draw Monitor
 * Measures the current CPU power consumption
 */

#include <string>
#include <cstdlib>
#include "modules/hardware/cpu_advanced.h"

namespace hardware::cpu_adv {

std::string executeCommand(const std::string& cmd);

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

} // namespace hardware::cpu_adv
