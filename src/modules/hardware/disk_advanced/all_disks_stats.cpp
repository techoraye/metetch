/**
 * All Disks Statistics Aggregator
 * Aggregates information from all mounted disks
 */

#include <vector>
#include "data_types.h"
#include "modules/hardware/disk_advanced.h"

namespace hardware::disk {

std::vector<DiskInfo> getDisksInfo();

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

} // namespace hardware::disk
