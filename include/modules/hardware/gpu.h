#pragma once
#include <string>

namespace hardware::gpu {
    struct GPUInfo {
        std::string device;
        std::string driver;
        float usage = 0.0f;           // GPU utilization percentage
        float memory_used = 0.0f;     // Memory used in MB
        float memory_total = 0.0f;    // Total memory in MB
        float temperature = 0.0f;     // Temperature in Celsius
        int power_draw = 0;           // Power draw in watts
    };
    
    GPUInfo getGPUInfo();
    std::string getDevice();
    std::string getDriver();
    float getGPUUsage();
    float getGPUTemperature();
    float getGPUMemoryUsed();
    float getGPUMemoryTotal();
    int getGPUPowerDraw();
}
