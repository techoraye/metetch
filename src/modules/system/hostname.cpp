/**
 * System Module: Hostname
 * Retrieves system hostname
 */

#include <string>
#include <unistd.h>
#include "modules/system/hostname.h"

namespace system::hostname {

std::string get() {
    char buf[256];
    if (gethostname(buf, sizeof(buf)) == 0) {
        return std::string(buf);
    }
    return "Unknown";
}

} // namespace system::hostname
