/**
 * Network Latency Measurement
 * Measures round-trip time (latency) to the internet
 */

#include <string>
#include <cstdlib>
#include "modules/network/advanced.h"

namespace net_advanced {

std::string executeCommand(const std::string& cmd);

// Get latency to google DNS
float getLatency() {
    std::string output = executeCommand("ping -c 1 8.8.8.8 2>/dev/null | grep 'time=' | awk -F'time=' '{print $2}' | awk '{print $1}' | sed 's/ms//'");
    if (!output.empty()) {
        try {
            return std::stof(output);
        } catch (...) {
            return 0.0f;
        }
    }
    return 0.0f;
}

} // namespace net_advanced
