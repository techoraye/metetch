/**
 * Used Disk Space Analyzer
 * Calculates total used disk space across all disks
 */

#include "modules/hardware/disk_advanced.h"

namespace hardware::disk {

AllDisksInfo getAllDisksInfo();

// Get used disk space
long getUsedDiskSpace() {
    AllDisksInfo info = getAllDisksInfo();
    return info.used_all_mb;
}

} // namespace hardware::disk
