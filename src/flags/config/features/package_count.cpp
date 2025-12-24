/**
 * Package Count Toggle Feature
 * Enable/disable package manager information
 */

#include "data_types.h"

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
    return "Show installed package count";
}
