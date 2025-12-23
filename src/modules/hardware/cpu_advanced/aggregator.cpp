/**
 * CPU Information Aggregator
 * Combines all advanced CPU info into a single structure
 */

#include "modules/hardware/cpu_advanced.h"

namespace hardware::cpu_adv {

// Forward declarations
float getCurrentFrequency();
float getMaxFrequency();
float getBaseFrequency();
int getCoreCount();
int getThreadCount();
float getTDP();
float getCPUPowerDraw();

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
