/**
 * Network Monitoring Toggle Feature
 * Enable/disable network information display
 */

#include "data_types.h"

void toggleNetworkMonitoring() {
    cfg.show_network = !cfg.show_network;
}

bool getNetworkMonitoringStatus() {
    return cfg.show_network;
}

const char* getNetworkMonitoringLabel() {
    return "Network Monitoring";
}

const char* getNetworkMonitoringDescription() {
    return "Show IP addresses, gateway, DNS, and network info";
}
