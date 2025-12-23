/**
 * Hardware Information Module - Pure C++ Implementation
 * No shell piping, clean and organized
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <cmath>
#include "modules/hardware.h"

using namespace std;

namespace hw {

string getCPUModel() {
    ifstream cpuinfo("/proc/cpuinfo");
    if (cpuinfo.is_open()) {
        string line;
        while (getline(cpuinfo, line)) {
            if (line.find("model name") == 0) {
                size_t pos = line.find(':');
                if (pos != string::npos) {
                    string model = line.substr(pos + 2);
                    // Clean up model name
                    model.erase(std::remove(model.begin(), model.end(), '('), model.end());
                    model.erase(std::remove(model.begin(), model.end(), ')'), model.end());
                    return model;
                }
            }
        }
    }
    return "Unknown CPU";
}

float getCPULoad() {
    ifstream loadavg("/proc/loadavg");
    if (loadavg.is_open()) {
        float load;
        loadavg >> load;
        loadavg.close();
        
        ifstream cpuinfo("/proc/cpuinfo");
        int cores = 0;
        string line;
        while (getline(cpuinfo, line)) {
            if (line.find("processor") == 0) cores++;
        }
        cpuinfo.close();
        
        if (cores > 0) {
            return (load / cores) * 100.0f;
        }
        return load * 100.0f;
    }
    return 0.0f;
}

float getCPUTemperature() {
    ifstream temp_file("/sys/class/thermal/thermal_zone0/temp");
    if (temp_file.is_open()) {
        int temp_raw;
        temp_file >> temp_raw;
        temp_file.close();
        return temp_raw / 1000.0f;
    }
    return -1.0f;
}

long getMemoryUsed() {
    struct sysinfo si;
    if (sysinfo(&si) == 0) {
        return (si.totalram - si.freeram) * si.mem_unit / 1024 / 1024;
    }
    return 0;
}

long getMemoryTotal() {
    struct sysinfo si;
    if (sysinfo(&si) == 0) {
        return si.totalram * si.mem_unit / 1024 / 1024;
    }
    return 0;
}

long getMemoryPercent() {
    struct sysinfo si;
    if (sysinfo(&si) == 0 && si.totalram > 0) {
        return ((si.totalram - si.freeram) * 100) / si.totalram;
    }
    return 0;
}

string getGPUDevice() {
    ifstream lspci("/proc/bus/pci/devices");
    if (lspci.is_open()) {
        string line;
        while (getline(lspci, line)) {
            if (line.find("0300") != string::npos || line.find("0302") != string::npos) {
                // Found GPU
                return "GPU Device";
            }
        }
    }
    return "Unknown GPU";
}

string getGPUDriver() {
    ifstream modules("/proc/modules");
    if (modules.is_open()) {
        string line;
        while (getline(modules, line)) {
            if (line.find("nvidia") != string::npos) return "NVIDIA";
            if (line.find("amdgpu") != string::npos) return "AMDGPU";
            if (line.find("i915") != string::npos) return "Intel i915";
        }
    }
    return "N/A";
}

string getDiskUsage() {
    struct statvfs st;
    if (statvfs("/", &st) == 0) {
        unsigned long long total = (unsigned long long)st.f_blocks * st.f_frsize;
        unsigned long long used = (unsigned long long)(st.f_blocks - st.f_bfree) * st.f_frsize;
        
        unsigned long total_gb = total / (1024 * 1024 * 1024);
        unsigned long used_gb = used / (1024 * 1024 * 1024);
        unsigned int percent = (total > 0) ? (used * 100) / total : 0;
        
        return to_string(used_gb) + " GB / " + to_string(total_gb) + " GB (" + to_string(percent) + "%)";
    }
    return "Unknown";
}

string getAudioDevice() {
    ifstream asound_cards("/proc/asound/cards");
    if (asound_cards.is_open()) {
        string line;
        while (getline(asound_cards, line)) {
            if (line.empty()) continue;
            size_t start = line.find('[');
            size_t end = line.find(']');
            if (start != string::npos && end != string::npos && end > start) {
                return line.substr(start + 1, end - start - 1);
            }
        }
    }
    return "N/A";
}

string getBatteryStatus() {
    ifstream battery("/sys/class/power_supply/BAT0/capacity");
    if (battery.is_open()) {
        int capacity;
        battery >> capacity;
        battery.close();
        
        ifstream status("/sys/class/power_supply/BAT0/status");
        string status_str = "Unknown";
        if (status.is_open()) {
            getline(status, status_str);
            status.close();
        }
        
        return to_string(capacity) + "% (" + status_str + ")";
    }
    return "N/A";
}

string getDisplayResolution() {
    // This requires X11 or Wayland, simplified for now
    return "N/A";
}

} // namespace hw
