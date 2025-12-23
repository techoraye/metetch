/**
 * Hardware Module: Display
 * Retrieves display resolution information
 */

#include <string>
#include <fstream>
#include "modules/hardware/display.h"

namespace hardware::display {

std::string getResolution() {
    // Try to get from sysfs first
    std::ifstream edid("/sys/class/drm/card0-HDMI-A-1/edid");
    if (edid.is_open()) {
        return "Display Connected";
    }
    
    return "N/A";
}

} // namespace hardware::display
