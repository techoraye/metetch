/**
 * Processes Display Feature Toggle
 * Modular feature for process information
 */

#include "data_types.h"

extern Config cfg;

void toggleProcessesDisplay() {
    cfg.show_processes = !cfg.show_processes;
}

bool getProcessesDisplayStatus() {
    return cfg.show_processes;
}

const char* getProcessesDisplayLabel() {
    return "Processes Display";
}

const char* getProcessesDisplayDescription() {
    return "Show active processes, threads, and system resource usage";
}
