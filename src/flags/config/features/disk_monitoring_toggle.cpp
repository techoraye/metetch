/**
 * Disk Monitoring Feature Toggle
 * Modular feature for disk/storage display
 */

#include "data_types.h"

extern Config cfg;

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
    return "Display disk usage, storage information, and filesystem details";
}
