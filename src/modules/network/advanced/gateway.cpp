/**
 * Default Gateway Retrieval
 * Fetches the system's default gateway address
 */

#include <string>
#include <cstdlib>
#include "modules/network/advanced.h"

namespace net_advanced {

std::string executeCommand(const std::string& cmd);

// Get default gateway
std::string getGateway() {
    std::string output = executeCommand("ip route show 2>/dev/null | grep 'default via' | awk '{print $3}' | head -1");
    if (!output.empty() && output.back() == '\n') output.pop_back();
    return output.empty() ? "N/A" : output;
}

} // namespace net_advanced
