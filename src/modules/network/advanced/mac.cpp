/**
 * MAC Address Retrieval
 * Fetches the primary MAC address from the system
 */

#include <string>
#include <cstdlib>
#include "modules/network/advanced.h"

namespace net_advanced {

std::string executeCommand(const std::string& cmd);

// Get MAC address
std::string getMACAddress() {
    std::string output = executeCommand("ip link show 2>/dev/null | grep -oP '(?<=link/ether\\s)[a-f0-9:]+' | head -1");
    if (!output.empty() && output.back() == '\n') output.pop_back();
    return output.empty() ? "N/A" : output;
}

} // namespace net_advanced
