/**
 * GPU Monitoring Feature Toggle
 * Modular feature for GPU display
 */

#include "data_types.h"

extern Config cfg;

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
    return "Display GPU device, usage, temperature, and memory information";
}
