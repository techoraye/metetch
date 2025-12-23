/**
 * Network Information Aggregator
 * Combines all advanced network info into a single structure
 */

#include <string>
#include "modules/network/advanced.h"

namespace net_advanced {

// Forward declarations
std::string getIPv4Address();
std::string getIPv6Address();
std::string getGateway();
std::string getDNS();
std::string getMACAddress();
long getBytesReceived();
long getBytesSent();
int getPacketLoss();
float getLatency();

// Get comprehensive advanced network info
NetworkAdvancedInfo getNetworkAdvancedInfo() {
    NetworkAdvancedInfo info;
    info.ipv4_address = getIPv4Address();
    info.ipv6_address = getIPv6Address();
    info.gateway = getGateway();
    info.dns_servers = getDNS();
    info.mac_address = getMACAddress();
    info.bytes_recv = getBytesReceived();
    info.bytes_sent = getBytesSent();
    info.packet_loss_percent = getPacketLoss();
    info.latency_ms = getLatency();
    
    return info;
}

} // namespace net_advanced
