/**
 * System Module: Kernel
 * Retrieves kernel version
 */

#include <string>
#include <sys/utsname.h>
#include "modules/system/kernel.h"

namespace system::kernel {

std::string get() {
    struct utsname buf;
    if (uname(&buf) == 0) {
        return std::string(buf.release);
    }
    return "Unknown";
}

} // namespace system::kernel
