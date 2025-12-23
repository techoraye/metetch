/**
 * Hardware Module: Audio
 * Retrieves audio system information
 */

#include <string>
#include <fstream>
#include "modules/hardware/audio.h"

namespace hardware::audio {

std::string getSystem() {
    // Check for PulseAudio
    std::ifstream pulse("/run/user/1000/pulse/native");
    if (pulse.is_open()) {
        return "PulseAudio";
    }
    
    // Check for ALSA
    std::ifstream alsa("/proc/asound");
    if (alsa.is_open()) {
        return "ALSA";
    }
    
    // Check for JACK
    std::ifstream jack("/tmp/jack-*");
    if (jack.is_open()) {
        return "JACK";
    }
    
    return "N/A";
}

} // namespace hardware::audio
