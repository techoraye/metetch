/**
 * System Module: Shell
 * Retrieves user shell
 */

#include <string>
#include <cstdlib>
#include "modules/system/shell.h"

namespace system::shell {

std::string get() {
    const char* shell_path = std::getenv("SHELL");
    if (!shell_path) return "Unknown";
    
    std::string shell(shell_path);
    size_t last_slash = shell.find_last_of("/");
    return last_slash != std::string::npos ? shell.substr(last_slash + 1) : shell;
}

} // namespace system::shell
