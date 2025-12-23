/**
 * Weather Display Toggle Feature
 * Enable/disable weather information
 */

#include "data_types.h"

void toggleWeatherDisplay() {
    cfg.show_weather = !cfg.show_weather;
}

bool getWeatherDisplayStatus() {
    return cfg.show_weather;
}

const char* getWeatherDisplayLabel() {
    return "Weather Display";
}

const char* getWeatherDisplayDescription() {
    return "Show current weather and temperature";
}
