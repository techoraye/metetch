/**
 * System Module: User Information
 * Retrieves current user details
 */

#include <string>
#include <unistd.h>
#include <pwd.h>
#include "modules/system/user.h"

namespace system::user {

std::string get() {
    uid_t uid = geteuid();
    struct passwd* pw = getpwuid(uid);
    return pw ? std::string(pw->pw_name) : "Unknown";
}

} // namespace system::user
