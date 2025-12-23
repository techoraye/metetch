/**
 * Network Module: IP Addresses
 * Retrieves local and public IP addresses
 */

#include <string>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include "modules/network/ip.h"

namespace network::ip {

std::string getLocal() {
    struct ifaddrs *ifaddr, *ifa;
    char host[NI_MAXHOST];
    
    if (getifaddrs(&ifaddr) == -1) {
        return "N/A";
    }
    
    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == nullptr) continue;
        
        if (ifa->ifa_addr->sa_family == AF_INET) {
            if (std::string(ifa->ifa_name) != "lo") {
                getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
                           host, NI_MAXHOST, nullptr, 0, NI_NUMERICHOST);
                freeifaddrs(ifaddr);
                return std::string(host);
            }
        }
    }
    
    freeifaddrs(ifaddr);
    return "N/A";
}

std::string getPublic() {
    // For now, return N/A - would require network request
    // Can be extended with async HTTP request
    return "N/A";
}

} // namespace network::ip
