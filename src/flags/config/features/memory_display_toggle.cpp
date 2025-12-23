/**
 * Memory Display Feature Toggle
 * Modular feature for memory information
 */

#include "data_types.h"

extern Config cfg;

void toggleMemoryDisplay() {
    cfg.show_memory = !cfg.show_memory;
}

bool getMemoryDisplayStatus() {
    return cfg.show_memory;
}

const char* getMemoryDisplayLabel() {
    return "Memory Display";
}

const char* getMemoryDisplayDescription() {
    return "Show RAM and swap memory usage with detailed statistics";
}
