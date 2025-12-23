/**
 * Hardware Module: CPU
 * Retrieves CPU model, load, and temperature
 */

#include <string>
#include <fstream>
#include <sstream>
#include "modules/hardware/cpu.h"

namespace hardware::cpu {

std::string getModel() {
    std::ifstream cpuinfo("/proc/cpuinfo");
    if (!cpuinfo.is_open()) return "Unknown CPU";
    
    std::string line;
    while (std::getline(cpuinfo, line)) {
        if (line.find("model name") == 0) {
            size_t colon = line.find(':');
            if (colon != std::string::npos) {
                std::string model = line.substr(colon + 2);
                if (!model.empty() && model.back() == '\n') model.pop_back();
                return model;
            }
        }
    }
    return "Unknown CPU";
}

float getLoad() {
    std::ifstream stat("/proc/stat");
    if (!stat.is_open()) return 0.0f;
    
    std::string line;
    std::getline(stat, line);
    stat.close();
    
    std::istringstream iss(line);
    std::string cpu_label;
    long user, nice, system, idle, iowait, irq, softirq;
    
    iss >> cpu_label >> user >> nice >> system >> idle >> iowait >> irq >> softirq;
    
    long total = user + nice + system + idle + iowait + irq + softirq;
    if (total == 0) return 0.0f;
    
    long busy = user + nice + system + irq + softirq;
    return (busy * 100.0f) / total;
}

float getTemperature() {
    std::ifstream thermal("/sys/class/thermal/thermal_zone0/temp");
    if (!thermal.is_open()) return -1.0f;
    
    int temp_millidegrees;
    thermal >> temp_millidegrees;
    thermal.close();
    
    return temp_millidegrees / 1000.0f;
}

} // namespace hardware::cpu
