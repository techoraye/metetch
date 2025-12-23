/**
 * System Module: Window Manager
 * Retrieves window manager information
 */

#include <string>
#include <cstdlib>
#include "modules/system/wm.h"

namespace system::wm {

std::string get() {
    const char* sway_socket = std::getenv("SWAYSOCK");
    if (sway_socket) return "Sway";
    
    const char* i3_socket = std::getenv("I3SOCK");
    if (i3_socket) return "i3";
    
    const char* wayland_display = std::getenv("WAYLAND_DISPLAY");
    if (wayland_display) return "Wayland";
    
    const char* display = std::getenv("DISPLAY");
    if (display) return "X11";
    
    return "N/A";
}

} // namespace system::wm
