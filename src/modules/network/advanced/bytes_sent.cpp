/**
 * Bytes Sent Tracker
 * Retrieves total bytes sent across all network interfaces
 */

#include <string>
#include <cstdlib>
#include "modules/network/advanced.h"

namespace net_advanced {

std::string executeCommand(const std::string& cmd);

// Get bytes sent
long getBytesSent() {
    std::string output = executeCommand("cat /proc/net/dev 2>/dev/null | tail -n +3 | awk '{sum+=$10} END {print sum}'");
    if (!output.empty()) {
        try {
            return std::stol(output);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

} // namespace net_advanced
