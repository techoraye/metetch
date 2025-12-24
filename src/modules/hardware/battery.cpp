/**
 * Hardware Module: Battery
 * Retrieves battery status information
 */

#include <string>
#include <fstream>
#include <sstream>
#include "modules/hardware/battery.h"

namespace hardware::battery {

std::string getStatus() {
    std::ifstream capacity("/sys/class/power_supply/BAT0/capacity");
    if (!capacity.is_open()) {
        return "N/A";
    }
    
    int percent;
    capacity >> percent;
    capacity.close();
    
    std::ifstream status_file("/sys/class/power_supply/BAT0/status");
    std::string status;
    if (status_file.is_open()) {
        std::getline(status_file, status);
        status_file.close();
    }
    
    std::ostringstream oss;
    oss << percent << "% (" << status << ")";
    return oss.str();
}

} // namespace hardware::battery
