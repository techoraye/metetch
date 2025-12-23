/**
 * Network Module: VPN
 * Retrieves VPN connection status
 */

#include <string>
#include <fstream>
#include <sstream>
#include "modules/network/vpn.h"

namespace network::vpn {

std::string getStatus() {
    std::ifstream route("/proc/net/route");
    if (!route.is_open()) {
        return "Inactive";
    }
    
    std::string line;
    std::getline(route, line); // Skip header
    
    // Check for VPN interfaces (tun*, tap*, wg*)
    while (std::getline(route, line)) {
        std::istringstream iss(line);
        std::string iface;
        iss >> iface;
        
        if (iface.find("tun") == 0 || iface.find("tap") == 0 || iface.find("wg") == 0) {
            route.close();
            return "Active";
        }
    }
    
    route.close();
    return "Inactive";
}

} // namespace network::vpn
