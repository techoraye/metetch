/**
 * All Disks Information Retriever
 * Gets information for all mounted disks
 */

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "data_types.h"
#include "modules/hardware/disk_advanced.h"

namespace hardware::disk {

std::string executeCommand(const std::string& cmd);
DiskInfo getDiskInfo(const std::string& mount_point);

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

} // namespace hardware::disk
