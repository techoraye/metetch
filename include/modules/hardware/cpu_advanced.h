#pragma once
#include <string>
#include <vector>

namespace hardware::cpu_adv {
    struct CPUCoreInfo {
        int core_id;
        float frequency_mhz;
        float usage_percent;
    };
    
    struct CPUAdvancedInfo {
        float max_frequency;
        float current_frequency;
        float base_frequency;
        int core_count;
        int thread_count;
        std::vector<CPUCoreInfo> cores;
        float thermal_design_power;  // TDP in watts
        float current_power_draw;    // Current power in watts
    };
    
    CPUAdvancedInfo getCPUAdvancedInfo();
    float getMaxFrequency();
    float getCurrentFrequency();
    int getCoreCount();
    int getThreadCount();
    float getTDP();
    float getCPUPowerDraw();
}
