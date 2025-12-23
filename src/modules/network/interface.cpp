/**
 * Network Module: Interface
 * Retrieves network interface information
 */

#include <string>
#include <fstream>
#include <sstream>
#include "modules/network/interface.h"

namespace network::interface {

std::string get() {
    std::ifstream route("/proc/net/route");
    if (!route.is_open()) {
        return "N/A";
    }
    
    std::string line;
    std::getline(route, line); // Skip header
    
    while (std::getline(route, line)) {
        std::istringstream iss(line);
        std::string iface;
        unsigned int dest;
        
        iss >> iface >> std::hex >> dest;
        
        // 0x00000000 = default route
        if (dest == 0 && iface != "lo") {
            route.close();
            return iface;
        }
    }
    
    route.close();
    return "N/A";
}

} // namespace network::interface
