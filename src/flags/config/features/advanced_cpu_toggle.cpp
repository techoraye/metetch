/**
 * Advanced CPU Feature Toggle
 * Modular feature for advanced CPU metrics
 */

#include "data_types.h"

extern Config cfg;

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
    return "Display detailed CPU metrics including frequency, cores, threads, and TDP";
}
