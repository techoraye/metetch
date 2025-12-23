/**
 * GPU Monitoring Toggle Feature
 * Enable/disable GPU information display
 */

#include "data_types.h"

void toggleGPUMonitoring() {
    cfg.show_gpu = !cfg.show_gpu;
}

bool getGPUMonitoringStatus() {
    return cfg.show_gpu;
}

const char* getGPUMonitoringLabel() {
    return "GPU Monitoring";
}

const char* getGPUMonitoringDescription() {
    return "Show GPU usage, temperature, and memory";
}
