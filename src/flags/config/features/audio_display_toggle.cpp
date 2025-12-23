/**
 * Audio Display Feature Toggle
 * Modular feature for audio system information
 */

#include "data_types.h"

extern Config cfg;

void toggleAudioDisplay() {
    cfg.show_audio = !cfg.show_audio;
}

bool getAudioDisplayStatus() {
    return cfg.show_audio;
}

const char* getAudioDisplayLabel() {
    return "Audio System Display";
}

const char* getAudioDisplayDescription() {
    return "Show audio device, sound server, and audio configuration";
}
