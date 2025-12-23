/**
 * Command Execution Helper
 * Provides utility function for executing system commands
 */

#include <string>
#include <cstdlib>
#include "modules/network/advanced.h"

namespace net_advanced {

// Helper to execute commands
std::string executeCommand(const std::string& cmd) {
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";
    
    std::string result;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

} // namespace net_advanced
