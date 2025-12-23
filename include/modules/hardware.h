#pragma once

#include <string>

namespace hw {
    std::string getCPUModel();
    float getCPULoad();
    float getCPUTemperature();
    long getMemoryUsed();
    long getMemoryTotal();
    long getMemoryPercent();
    std::string getGPUDevice();
    std::string getGPUDriver();
    std::string getDiskUsage();
    std::string getAudioDevice();
    std::string getBatteryStatus();
    std::string getDisplayResolution();
}

// Include advanced modules
#include "hardware/gpu.h"
#include "hardware/cpu_advanced.h"
#include "hardware/disk_advanced.h"
