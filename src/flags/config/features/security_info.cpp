/**
 * Security Information Toggle Feature
 * Enable/disable security and firewall status
 */

#include "data_types.h"

void toggleSecurityInfo() {
    cfg.show_security = !cfg.show_security;
}

bool getSecurityInfoStatus() {
    return cfg.show_security;
}

const char* getSecurityInfoLabel() {
    return "Security Information";
}

const char* getSecurityInfoDescription() {
    return "Show firewall, SELinux, AppArmor status";
}
