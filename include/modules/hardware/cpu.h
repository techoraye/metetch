#pragma once
#include <string>

namespace hardware::cpu {
    std::string getModel();
    float getLoad();
    float getTemperature();
}
