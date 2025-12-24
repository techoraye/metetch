/**
 * Network Monitoring Feature Toggle
 * Modular feature for network display
 */

#include "data_types.h"

extern Config cfg;

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
    return "Display network interfaces, IP addresses, VPN status, and advanced network stats";
}
