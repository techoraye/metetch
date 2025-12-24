#pragma once
#include <string>
#include <vector>

namespace hardware::disk {
    // Disk information struct
    struct DiskInfo {
        std::string device;          // Device name (sda, nvme0n1, etc.)
        std::string mount_point;     // Mount point (/, /home, etc.)
        std::string filesystem;      // Filesystem type (ext4, btrfs, etc.)
        long total_mb = 0;           // Total size in MB
        long used_mb = 0;            // Used space in MB
        long free_mb = 0;            // Free space in MB
        int percent_used = 0;        // Percentage used
        std::string status;          // Health status
    };
    
    // AllDisksInfo struct to be used within the namespace
    struct AllDisksInfo {
        std::vector<DiskInfo> disks;
        long total_all_mb = 0;
        long used_all_mb = 0;
        long free_all_mb = 0;
        int percent_used_avg = 0;
    };
    
    AllDisksInfo getAllDisksInfo();
    std::vector<DiskInfo> getDisksInfo();
    DiskInfo getDiskInfo(const std::string& mount_point);
    long getTotalDiskSpace();
    long getUsedDiskSpace();
    long getFreeDiskSpace();
    int getDiskUsagePercent();
}
