/**
 * IPv6 Address Retrieval
 * Fetches the active IPv6 address from the system
 */

#include <string>
#include <cstdlib>
#include "modules/network/advanced.h"

namespace net_advanced {

std::string executeCommand(const std::string& cmd);

// Get IPv6 address
std::string getIPv6Address() {
    std::string output = executeCommand("ip -6 addr show 2>/dev/null | grep -oP '(?<=inet6\\s)[a-f0-9:]+' | grep -v '^fe80' | head -1");
    if (!output.empty() && output.back() == '\n') output.pop_back();
    return output.empty() ? "N/A" : output;
}

} // namespace net_advanced
