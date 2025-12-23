/**
 * Configuration Saver
 * Persists configuration to file
 */

#include <string>
#include <fstream>
#include "data_types.h"

using namespace std;

extern string configPath();

void saveConfig() {
    ofstream f(configPath());
    if (!f.is_open()) return;
    f << "show_network=" << (cfg.show_network ? "1" : "0") << "\n";
    f << "show_battery=" << (cfg.show_battery ? "1" : "0") << "\n";
    f << "show_weather=" << (cfg.show_weather ? "1" : "0") << "\n";
    f << "show_cpu_advanced=" << (cfg.show_cpu_advanced ? "1" : "0") << "\n";
    f << "show_security=" << (cfg.show_security ? "1" : "0") << "\n";
    f << "show_packages=" << (cfg.show_packages ? "1" : "0") << "\n";
    f << "show_gpu=" << (cfg.show_gpu ? "1" : "0") << "\n";
    f << "show_disk=" << (cfg.show_disk ? "1" : "0") << "\n";
    f << "show_uptime=" << (cfg.show_uptime ? "1" : "0") << "\n";
    f << "show_memory=" << (cfg.show_memory ? "1" : "0") << "\n";
    f << "show_load=" << (cfg.show_load ? "1" : "0") << "\n";
    f << "show_processes=" << (cfg.show_processes ? "1" : "0") << "\n";
    f << "show_audio=" << (cfg.show_audio ? "1" : "0") << "\n";
    f << "show_display=" << (cfg.show_display ? "1" : "0") << "\n";
    f << "theme=" << cfg.theme << "\n";
}
