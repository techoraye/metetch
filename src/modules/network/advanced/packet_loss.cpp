/**
 * Packet Loss Measurement
 * Measures network packet loss percentage to the internet
 */

#include <string>
#include <cstdlib>
#include "modules/network/advanced.h"

namespace net_advanced {

std::string executeCommand(const std::string& cmd);

// Get packet loss percentage
int getPacketLoss() {
    std::string output = executeCommand("ping -c 5 8.8.8.8 2>/dev/null | grep 'loss' | awk '{print $6}' | sed 's/%//'");
    if (!output.empty()) {
        try {
            return std::stoi(output);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

} // namespace net_advanced
