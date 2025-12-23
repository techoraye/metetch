/**
 * Network Information Module - Pure C++ Implementation
 * No shell piping, clean and organized
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <unistd.h>
#include "modules/network.h"

using namespace std;

namespace net {

string getLocalIP() {
    struct ifaddrs* ifaddr;
    if (getifaddrs(&ifaddr) == -1) {
        return "N/A";
    }
    
    string local_ip = "N/A";
    for (struct ifaddrs* ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) continue;
        
        if (ifa->ifa_addr->sa_family == AF_INET) {
            struct sockaddr_in* addr = (struct sockaddr_in*)ifa->ifa_addr;
            string ip = inet_ntoa(addr->sin_addr);
            
            if (ip != "127.0.0.1" && ip.find("169.254") == string::npos) {
                local_ip = ip;
                break;
            }
        }
    }
    
    freeifaddrs(ifaddr);
    return local_ip;
}

string getPublicIP() {
    // Try to read from DNS queries or cache
    // For now, return placeholder
    return "N/A";
}

string getNetworkInterface() {
    struct ifaddrs* ifaddr;
    if (getifaddrs(&ifaddr) == -1) {
        return "N/A";
    }
    
    string interface = "N/A";
    for (struct ifaddrs* ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) continue;
        if (ifa->ifa_addr->sa_family != AF_INET) continue;
        
        struct sockaddr_in* addr = (struct sockaddr_in*)ifa->ifa_addr;
        string ip = inet_ntoa(addr->sin_addr);
        
        if (ip != "127.0.0.1" && ip.find("169.254") == string::npos) {
            interface = ifa->ifa_name;
            break;
        }
    }
    
    freeifaddrs(ifaddr);
    return interface;
}

string getVPNStatus() {
    ifstream tun_tap("/sys/class/net");
    
    // Check for TUN/TAP devices
    ifstream routes("/proc/net/route");
    if (routes.is_open()) {
        string line;
        while (getline(routes, line)) {
            if (line.find("tun") != string::npos ||
                line.find("tap") != string::npos ||
                line.find("wg") != string::npos) {
                return "Active";
            }
        }
    }
    
    return "Inactive";
}

} // namespace net
