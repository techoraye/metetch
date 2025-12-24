#pragma once
#include <string>

namespace net_advanced {
    struct NetworkAdvancedInfo {
        std::string ipv4_address;
        std::string ipv6_address;
        std::string gateway;
        std::string dns_servers;
        std::string mac_address;
        long bytes_recv;
        long bytes_sent;
        long packets_recv;
        long packets_sent;
        int packet_loss_percent;
        float latency_ms;
    };
    
    NetworkAdvancedInfo getNetworkAdvancedInfo();
    std::string getIPv4Address();
    std::string getIPv6Address();
    std::string getGateway();
    std::string getDNS();
    std::string getMACAddress();
    long getBytesReceived();
    long getBytesSent();
    int getPacketLoss();
    float getLatency();
}
