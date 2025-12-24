/**
 * Free Disk Space Analyzer
 * Calculates total free disk space across all disks
 */

#include "modules/hardware/disk_advanced.h"

namespace hardware::disk {

AllDisksInfo getAllDisksInfo();

// Get free disk space
long getFreeDiskSpace() {
    AllDisksInfo info = getAllDisksInfo();
    return info.free_all_mb;
}

} // namespace hardware::disk
