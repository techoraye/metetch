/**
 * Security Info Feature Toggle
 * Modular feature for security information
 */

#include "data_types.h"

extern Config cfg;

void toggleSecurityInfo() {
    cfg.show_security = !cfg.show_security;
}

bool getSecurityInfoStatus() {
    return cfg.show_security;
}

const char* getSecurityInfoLabel() {
    return "Security Info";
}

const char* getSecurityInfoDescription() {
    return "Show security features, firewall status, and SELinux/AppArmor info";
}
