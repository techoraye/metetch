/**
 * System Module: Desktop Environment
 * Retrieves desktop environment information
 */

#include <string>
#include <cstdlib>
#include "modules/system/desktop.h"

namespace system::desktop {

std::string get() {
    const char* de = std::getenv("XDG_CURRENT_DESKTOP");
    if (!de) de = std::getenv("DESKTOP_SESSION");
    return de ? std::string(de) : "N/A";
}

} // namespace system::desktop
