/**
 * System Module: Terminal
 * Retrieves terminal type
 */

#include <string>
#include <cstdlib>
#include "modules/system/terminal.h"

namespace system::terminal {

std::string get() {
    const char* term = std::getenv("TERM");
    return term ? std::string(term) : "Unknown";
}

} // namespace system::terminal
