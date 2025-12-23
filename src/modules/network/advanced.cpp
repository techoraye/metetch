/**
 * Network Module: Advanced Network Information
 * Retrieves detailed network statistics, DNS, gateway, and connection info
 */

#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "modules/network/advanced.h"

namespace net_advanced {

// Helper to execute commands
std::string executeCommand(const std::string& cmd) {
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";
    
    std::string result;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

// Get IPv4 address
std::string getIPv4Address() {
    std::string output = executeCommand("ip -4 addr show 2>/dev/null | grep -oP '(?<=inet\\s)\\d+(\\.\\d+){3}' | head -1");
    if (!output.empty() && output.back() == '\n') output.pop_back();
    return output.empty() ? "N/A" : output;
}

// Get IPv6 address
std::string getIPv6Address() {
    std::string output = executeCommand("ip -6 addr show 2>/dev/null | grep -oP '(?<=inet6\\s)[a-f0-9:]+' | grep -v '^fe80' | head -1");
    if (!output.empty() && output.back() == '\n') output.pop_back();
    return output.empty() ? "N/A" : output;
}

// Get default gateway
std::string getGateway() {
    std::string output = executeCommand("ip route show 2>/dev/null | grep 'default via' | awk '{print $3}' | head -1");
    if (!output.empty() && output.back() == '\n') output.pop_back();
    return output.empty() ? "N/A" : output;
}

// Get DNS servers
std::string getDNS() {
    std::string output = executeCommand("cat /etc/resolv.conf 2>/dev/null | grep 'nameserver' | awk '{print $2}' | tr '\\n' ',' | sed 's/,$//'");
    if (!output.empty() && output.back() == '\n') output.pop_back();
    return output.empty() ? "N/A" : output;
}

// Get MAC address
std::string getMACAddress() {
    std::string output = executeCommand("ip link show 2>/dev/null | grep -oP '(?<=link/ether\\s)[a-f0-9:]+' | head -1");
    if (!output.empty() && output.back() == '\n') output.pop_back();
    return output.empty() ? "N/A" : output;
}

// Get bytes received
long getBytesReceived() {
    std::string output = executeCommand("cat /proc/net/dev 2>/dev/null | tail -n +3 | awk '{sum+=$2} END {print sum}'");
    if (!output.empty()) {
        try {
            return std::stol(output);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

// Get bytes sent
long getBytesSent() {
    std::string output = executeCommand("cat /proc/net/dev 2>/dev/null | tail -n +3 | awk '{sum+=$10} END {print sum}'");
    if (!output.empty()) {
        try {
            return std::stol(output);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

// Get packet loss percentage
int getPacketLoss() {
    std::string output = executeCommand("ping -c 5 8.8.8.8 2>/dev/null | grep 'loss' | awk '{print $6}' | sed 's/%//'");
    if (!output.empty()) {
        try {
            return std::stoi(output);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

// Get latency to google DNS
float getLatency() {
    std::string output = executeCommand("ping -c 1 8.8.8.8 2>/dev/null | grep 'time=' | awk -F'time=' '{print $2}' | awk '{print $1}' | sed 's/ms//'");
    if (!output.empty()) {
        try {
            return std::stof(output);
        } catch (...) {
            return 0.0f;
        }
    }
    return 0.0f;
}

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

} // namespace network::advanced
