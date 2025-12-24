/**
 * Advanced CPU Toggle Feature
 * Enable/disable detailed CPU information
 */

#include "data_types.h"

void toggleAdvancedCPU() {
    cfg.show_cpu_advanced = !cfg.show_cpu_advanced;
}

bool getAdvancedCPUStatus() {
    return cfg.show_cpu_advanced;
}

const char* getAdvancedCPULabel() {
    return "Advanced CPU Info";
}

const char* getAdvancedCPUDescription() {
    return "Show CPU frequency, cores, threads, and power";
}
