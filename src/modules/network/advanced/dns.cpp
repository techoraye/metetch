/**
 * DNS Server Retrieval
 * Fetches configured DNS servers from the system
 */

#include <string>
#include <cstdlib>
#include "modules/network/advanced.h"

namespace net_advanced {

std::string executeCommand(const std::string& cmd);

// Get DNS servers
std::string getDNS() {
    std::string output = executeCommand("cat /etc/resolv.conf 2>/dev/null | grep 'nameserver' | awk '{print $2}' | tr '\\n' ',' | sed 's/,$//'");
    if (!output.empty() && output.back() == '\n') output.pop_back();
    return output.empty() ? "N/A" : output;
}

} // namespace net_advanced
