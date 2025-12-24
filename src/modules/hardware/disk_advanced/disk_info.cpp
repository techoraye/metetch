/**
 * Disk Information Retriever
 * Gets detailed information for a specific disk mount point
 */

#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sys/statvfs.h>
#include "data_types.h"
#include "modules/hardware/disk_advanced.h"

namespace hardware::disk {

std::string executeCommand(const std::string& cmd);

// Get disk information for a specific mount point
DiskInfo getDiskInfo(const std::string& mount_point) {
    DiskInfo info;
    info.mount_point = mount_point;
    
    struct statvfs st;
    if (statvfs(mount_point.c_str(), &st) == 0) {
        info.total_mb = (st.f_blocks * st.f_frsize) / 1024 / 1024;
        info.free_mb = (st.f_bavail * st.f_frsize) / 1024 / 1024;
        info.used_mb = info.total_mb - info.free_mb;
        info.percent_used = info.total_mb > 0 ? (info.used_mb * 100) / info.total_mb : 0;
        
        // Get filesystem type
        std::string df_output = executeCommand("df -T '" + mount_point + "' 2>/dev/null | tail -1 | awk '{print $2}'");
        if (!df_output.empty() && df_output.back() == '\n') df_output.pop_back();
        info.filesystem = df_output.empty() ? "Unknown" : df_output;
        
        // Try to get device name from df (will be overridden if set by caller)
        if (info.device.empty()) {
            std::string device_output = executeCommand("df '" + mount_point + "' 2>/dev/null | tail -1 | awk '{print $1}'");
            if (!device_output.empty() && device_output.back() == '\n') device_output.pop_back();
            info.device = device_output.empty() ? "Unknown" : device_output;
        }
        
        // Determine status
        if (info.percent_used >= 95) {
            info.status = "CRITICAL";
        } else if (info.percent_used >= 85) {
            info.status = "WARNING";
        } else if (info.percent_used >= 70) {
            info.status = "CAUTION";
        } else {
            info.status = "OK";
        }
    }
    
    return info;
}

} // namespace hardware::disk
