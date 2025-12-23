/**
 * Update Checker
 * Checks for available updates
 */

#include <string>
#include "utils.h"
#include "data_types.h"

using namespace std;

extern const string api;
extern const string ver;

bool checkUpd() {
    string remote = httpGet(api);
    if (remote.empty()) return false;
    string localVer = ver;
    return isNewer(remote, localVer);
}
