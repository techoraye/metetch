/**
 * Hardware Module: Disk
 * Retrieves disk usage information
 */

#include <string>
#include <sys/statvfs.h>
#include <sstream>
#include <iomanip>
#include "modules/hardware/disk.h"

namespace hardware::disk {

std::string getUsage() {
    struct statvfs stat;
    if (statvfs("/", &stat) != 0) {
        return "Unknown";
    }
    
    long total_blocks = stat.f_blocks * stat.f_frsize / (1024 * 1024);
    long used_blocks = (stat.f_blocks - stat.f_bfree) * stat.f_frsize / (1024 * 1024);
    long percent = total_blocks > 0 ? (used_blocks * 100) / total_blocks : 0;
    
    std::ostringstream oss;
    oss << used_blocks << " / " << total_blocks << " MB (" << percent << "%)";
    return oss.str();
}

} // namespace hardware::disk
