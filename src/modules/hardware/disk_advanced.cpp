/**
 * Hardware Module: Advanced Disk Information
 * Retrieves detailed disk information for all mounted disks
 */

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sys/statvfs.h>
#include "data_types.h"
#include "modules/hardware/disk_advanced.h"

namespace hardware::disk {

// Helper to execute commands
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

// Get all mounted disks
std::vector<DiskInfo> getDisksInfo() {
    std::vector<DiskInfo> disks;
    
    // Get all mount points from /proc/mounts
    std::string mount_output = executeCommand("cat /proc/mounts | grep -E '^/dev' | awk '{print $1, $2}' | sort -k2 | uniq");
    if (!mount_output.empty()) {
        std::istringstream iss(mount_output);
        std::string device, mount_point;
        while (iss >> device >> mount_point) {
            if (!device.empty() && !mount_point.empty()) {
                DiskInfo disk = getDiskInfo(mount_point);
                if (disk.total_mb > 0) {
                    disk.device = device;  // Override with actual device name
                    disks.push_back(disk);
                }
            }
        }
    } else {
        // Fallback to common mount points
        for (const auto& mount : {"/", "/home", "/boot", "/var"}) {
            DiskInfo disk = getDiskInfo(mount);
            if (disk.total_mb > 0) {
                disks.push_back(disk);
            }
        }
    }
    
    return disks;
}

// Get all disks information combined
AllDisksInfo getAllDisksInfo() {
    AllDisksInfo all_info;
    all_info.disks = getDisksInfo();
    
    all_info.total_all_mb = 0;
    all_info.used_all_mb = 0;
    all_info.free_all_mb = 0;
    
    // Calculate totals
    for (const auto& disk : all_info.disks) {
        all_info.total_all_mb += disk.total_mb;
        all_info.used_all_mb += disk.used_mb;
        all_info.free_all_mb += disk.free_mb;
    }
    
    // Calculate average percentage
    all_info.percent_used_avg = all_info.total_all_mb > 0 
        ? (all_info.used_all_mb * 100) / all_info.total_all_mb 
        : 0;
    
    return all_info;
}

// Get total disk space
long getTotalDiskSpace() {
    AllDisksInfo info = getAllDisksInfo();
    return info.total_all_mb;
}

// Get used disk space
long getUsedDiskSpace() {
    AllDisksInfo info = getAllDisksInfo();
    return info.used_all_mb;
}

// Get free disk space
long getFreeDiskSpace() {
    AllDisksInfo info = getAllDisksInfo();
    return info.free_all_mb;
}

// Get disk usage percentage
int getDiskUsagePercent() {
    AllDisksInfo info = getAllDisksInfo();
    return info.percent_used_avg;
}

} // namespace hardware::disk
