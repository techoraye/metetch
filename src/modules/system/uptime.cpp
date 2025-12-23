/**
 * System Module: Uptime
 * Retrieves system uptime
 */

#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "modules/system/uptime.h"

namespace system::uptime {

std::string get() {
    std::ifstream uptime_file("/proc/uptime");
    if (!uptime_file.is_open()) return "Unknown";
    
    double uptime_seconds;
    uptime_file >> uptime_seconds;
    uptime_file.close();
    
    long days = static_cast<long>(uptime_seconds) / 86400;
    long hours = (static_cast<long>(uptime_seconds) % 86400) / 3600;
    long minutes = (static_cast<long>(uptime_seconds) % 3600) / 60;
    
    std::ostringstream oss;
    if (days > 0) oss << days << "d ";
    if (hours > 0) oss << hours << "h ";
    oss << minutes << "m";
    
    return oss.str();
}

} // namespace system::uptime
