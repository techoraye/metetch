/**
 * Disk Usage Percentage Calculator
 * Calculates disk usage percentage across all disks
 */

#include "modules/hardware/disk_advanced.h"

namespace hardware::disk {

AllDisksInfo getAllDisksInfo();

// Get disk usage percentage
int getDiskUsagePercent() {
    AllDisksInfo info = getAllDisksInfo();
    return info.percent_used_avg;
}

} // namespace hardware::disk
