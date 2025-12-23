/**
 * Hardware Module: GPU
 * Retrieves GPU device, driver, usage, temperature, and memory information
 * Supports NVIDIA, AMD, and Intel GPUs
 */

#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "modules/hardware/gpu.h"

namespace hardware::gpu {

// Helper function to read system file
std::string readSysFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return "";
    std::string content, line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    return content;
}

// Helper function to execute command and capture output
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

// Get GPU device information
std::string getDevice() {
    // Try NVIDIA
    std::string nvidia_output = executeCommand("lspci 2>/dev/null | grep -i nvidia | head -1");
    if (!nvidia_output.empty()) {
        size_t pos = nvidia_output.find(": ");
        if (pos != std::string::npos) {
            return nvidia_output.substr(pos + 2);
        }
        return "NVIDIA GPU";
    }
    
    // Try AMD
    std::string amd_output = executeCommand("lspci 2>/dev/null | grep -i amd | grep -i vga | head -1");
    if (!amd_output.empty()) {
        size_t pos = amd_output.find(": ");
        if (pos != std::string::npos) {
            return amd_output.substr(pos + 2);
        }
        return "AMD GPU";
    }
    
    // Try Intel
    std::string intel_output = executeCommand("lspci 2>/dev/null | grep -i intel | grep -i vga | head -1");
    if (!intel_output.empty()) {
        size_t pos = intel_output.find(": ");
        if (pos != std::string::npos) {
            return intel_output.substr(pos + 2);
        }
        return "Intel GPU";
    }
    
    // Try generic VGA
    std::string vga_output = executeCommand("lspci 2>/dev/null | grep -i 'vga\\|display\\|3d' | head -1");
    if (!vga_output.empty()) {
        size_t pos = vga_output.find(": ");
        if (pos != std::string::npos) {
            return vga_output.substr(pos + 2);
        }
    }
    
    return "Unknown GPU";
}

// Get GPU driver information
std::string getDriver() {
    // Check for NVIDIA
    std::ifstream nvidia("/proc/driver/nvidia/version");
    if (nvidia.is_open()) {
        std::string line;
        std::getline(nvidia, line);
        return "NVIDIA " + line;
    }
    
    // Check for AMDGPU
    std::string amd_check = executeCommand("lsmod 2>/dev/null | grep -i amdgpu");
    if (!amd_check.empty()) {
        return "AMDGPU Driver";
    }
    
    // Check for Radeon
    std::string radeon_check = executeCommand("lsmod 2>/dev/null | grep -i radeon");
    if (!radeon_check.empty()) {
        return "Radeon Driver";
    }
    
    // Check for Intel i915
    std::string intel_check = executeCommand("lsmod 2>/dev/null | grep -i i915");
    if (!intel_check.empty()) {
        return "Intel i915 Driver";
    }
    
    // Check for Nouveau (NVIDIA open source)
    std::string nouveau_check = executeCommand("lsmod 2>/dev/null | grep -i nouveau");
    if (!nouveau_check.empty()) {
        return "Nouveau Driver";
    }
    
    return "N/A";
}

// Get NVIDIA GPU usage via nvidia-smi
float getNVIDIAUsage() {
    std::string output = executeCommand("nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits 2>/dev/null | head -1");
    if (!output.empty()) {
        try {
            return std::stof(output);
        } catch (...) {
            return 0.0f;
        }
    }
    return 0.0f;
}

// Get AMD GPU usage via rocm-smi or amdgpu metrics
float getAMDUsage() {
    // Try rocm-smi first
    std::string output = executeCommand("rocm-smi --showuse 2>/dev/null | grep 'GPU use' | awk '{print $NF}' | head -1");
    if (!output.empty() && output.find("%") != std::string::npos) {
        try {
            std::string num = output.substr(0, output.find("%"));
            return std::stof(num);
        } catch (...) {
            return 0.0f;
        }
    }
    
    // Try amdgpu metrics
    output = executeCommand("cat /sys/kernel/debug/dri/*/amdgpu_pm_info 2>/dev/null | grep 'GPU Load' | awk '{print $NF}'");
    if (!output.empty()) {
        try {
            std::string num = output.substr(0, output.find("%"));
            return std::stof(num);
        } catch (...) {
            return 0.0f;
        }
    }
    
    return 0.0f;
}

// Get Intel GPU usage
float getIntelUsage() {
    std::string output = executeCommand("cat /sys/class/drm/card0/gt_cur_freq_mhz 2>/dev/null");
    if (!output.empty()) {
        // This is frequency, not utilization - estimate based on frequency
        try {
            float freq = std::stof(output);
            // Rough estimation (assuming max freq ~1500 MHz)
            return (freq / 1500.0f) * 100.0f;
        } catch (...) {
            return 0.0f;
        }
    }
    return 0.0f;
}

// Get GPU usage percentage
float getGPUUsage() {
    // Try NVIDIA first
    float usage = getNVIDIAUsage();
    if (usage > 0.0f) return usage;
    
    // Try AMD
    usage = getAMDUsage();
    if (usage > 0.0f) return usage;
    
    // Try Intel
    usage = getIntelUsage();
    if (usage > 0.0f) return usage;
    
    return 0.0f;
}

// Get NVIDIA GPU temperature
float getNVIDIATemperature() {
    std::string output = executeCommand("nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader,nounits 2>/dev/null | head -1");
    if (!output.empty()) {
        try {
            return std::stof(output);
        } catch (...) {
            return 0.0f;
        }
    }
    return 0.0f;
}

// Get AMD GPU temperature
float getAMDTemperature() {
    std::string output = executeCommand("rocm-smi --showtemp 2>/dev/null | grep 'Temperature' | awk '{print $(NF-1)}' | head -1");
    if (!output.empty()) {
        try {
            return std::stof(output);
        } catch (...) {
            return 0.0f;
        }
    }
    return 0.0f;
}

// Get GPU temperature in Celsius
float getGPUTemperature() {
    // Try NVIDIA
    float temp = getNVIDIATemperature();
    if (temp > 0.0f) return temp;
    
    // Try AMD
    temp = getAMDTemperature();
    if (temp > 0.0f) return temp;
    
    return 0.0f;
}

// Get NVIDIA GPU memory usage
std::pair<float, float> getNVIDIAMemory() {
    std::string output = executeCommand("nvidia-smi --query-gpu=memory.used,memory.total --format=csv,noheader,nounits 2>/dev/null | head -1");
    if (!output.empty()) {
        try {
            size_t comma_pos = output.find(',');
            if (comma_pos != std::string::npos) {
                float used = std::stof(output.substr(0, comma_pos));
                float total = std::stof(output.substr(comma_pos + 1));
                return {used, total};
            }
        } catch (...) {
            return {0.0f, 0.0f};
        }
    }
    return {0.0f, 0.0f};
}

// Get AMD GPU memory usage
std::pair<float, float> getAMDMemory() {
    std::string output = executeCommand("rocm-smi --showmeminfo 2>/dev/null | grep 'Total Memory' | awk '{print $(NF-1)}' | head -1");
    if (!output.empty()) {
        try {
            float total = std::stof(output) / 1024.0f; // Convert from MB to MB
            // Try to get used memory
            std::string used_output = executeCommand("rocm-smi --showproductname 2>/dev/null | wc -l");
            float used = total * 0.5f; // Rough estimation
            return {used, total};
        } catch (...) {
            return {0.0f, 0.0f};
        }
    }
    return {0.0f, 0.0f};
}

// Get GPU memory used in MB
float getGPUMemoryUsed() {
    auto nvidia = getNVIDIAMemory();
    if (nvidia.second > 0.0f) return nvidia.first;
    
    auto amd = getAMDMemory();
    if (amd.second > 0.0f) return amd.first;
    
    return 0.0f;
}

// Get GPU memory total in MB
float getGPUMemoryTotal() {
    auto nvidia = getNVIDIAMemory();
    if (nvidia.second > 0.0f) return nvidia.second;
    
    auto amd = getAMDMemory();
    if (amd.second > 0.0f) return amd.second;
    
    return 0.0f;
}

// Get GPU power draw in watts
int getGPUPowerDraw() {
    // NVIDIA power draw
    std::string output = executeCommand("nvidia-smi --query-gpu=power.draw --format=csv,noheader,nounits 2>/dev/null | head -1");
    if (!output.empty()) {
        try {
            return static_cast<int>(std::stof(output));
        } catch (...) {
            return 0;
        }
    }
    
    // AMD power draw
    output = executeCommand("rocm-smi --showpower 2>/dev/null | grep 'Power' | awk '{print $(NF-1)}' | head -1");
    if (!output.empty()) {
        try {
            return static_cast<int>(std::stof(output));
        } catch (...) {
            return 0;
        }
    }
    
    return 0;
}

// Get comprehensive GPU information
GPUInfo getGPUInfo() {
    GPUInfo info;
    info.device = getDevice();
    info.driver = getDriver();
    info.usage = getGPUUsage();
    info.temperature = getGPUTemperature();
    info.memory_used = getGPUMemoryUsed();
    info.memory_total = getGPUMemoryTotal();
    info.power_draw = getGPUPowerDraw();
    
    return info;
}

} // namespace hardware::gpu

