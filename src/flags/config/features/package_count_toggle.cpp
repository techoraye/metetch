/**
 * Package Count Feature Toggle
 * Modular feature for package statistics
 */

#include "data_types.h"

extern Config cfg;

void togglePackageCount() {
    cfg.show_packages = !cfg.show_packages;
}

bool getPackageCountStatus() {
    return cfg.show_packages;
}

const char* getPackageCountLabel() {
    return "Package Count";
}

const char* getPackageCountDescription() {
    return "Display installed package statistics and summary";
}
