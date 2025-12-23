/**
 * Disk Monitoring Toggle Feature
 * Enable/disable disk usage information display
 */

#include "data_types.h"

void toggleDiskMonitoring() {
    cfg.show_disk = !cfg.show_disk;
}

bool getDiskMonitoringStatus() {
    return cfg.show_disk;
}

const char* getDiskMonitoringLabel() {
    return "Disk Monitoring";
}

const char* getDiskMonitoringDescription() {
    return "Show disk usage across all mounted filesystems";
}
