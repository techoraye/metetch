/**
 * Total Disk Space Analyzer
 * Calculates total disk space across all disks
 */

#include "modules/hardware/disk_advanced.h"

namespace hardware::disk {

AllDisksInfo getAllDisksInfo();

// Get total disk space
long getTotalDiskSpace() {
    AllDisksInfo info = getAllDisksInfo();
    return info.total_all_mb;
}

} // namespace hardware::disk
