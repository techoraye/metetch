/**
 * IPv4 Address Retrieval
 * Fetches the active IPv4 address from the system
 */

#include <string>
#include <cstdlib>
#include "modules/network/advanced.h"

namespace net_advanced {

std::string executeCommand(const std::string& cmd);

// Get IPv4 address
std::string getIPv4Address() {
    std::string output = executeCommand("ip -4 addr show 2>/dev/null | grep -oP '(?<=inet\\s)\\d+(\\.\\d+){3}' | head -1");
    if (!output.empty() && output.back() == '\n') output.pop_back();
    return output.empty() ? "N/A" : output;
}

} // namespace net_advanced
