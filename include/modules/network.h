#pragma once

#include <string>

namespace net {
    std::string getLocalIP();
    std::string getPublicIP();
    std::string getNetworkInterface();
    std::string getVPNStatus();
}
