/**
 * Configuration Loader
 * Loads configuration from file
 */

#include <string>
#include <fstream>
#include "data_types.h"

using namespace std;

extern string configPath();

void loadConfig() {
    ifstream f(configPath());
    if (!f.is_open()) return;
    string line;
    while (getline(f, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto pos = line.find('=');
        if (pos == string::npos) continue;
        string k = line.substr(0, pos);
        string v = line.substr(pos+1);
        if (k == "show_network") cfg.show_network = (v == "1");
        else if (k == "show_battery") cfg.show_battery = (v == "1");
        else if (k == "show_weather") cfg.show_weather = (v == "1");
        else if (k == "show_cpu_advanced") cfg.show_cpu_advanced = (v == "1");
        else if (k == "show_security") cfg.show_security = (v == "1");
        else if (k == "show_packages") cfg.show_packages = (v == "1");
        else if (k == "show_gpu") cfg.show_gpu = (v == "1");
        else if (k == "show_disk") cfg.show_disk = (v == "1");
        else if (k == "show_uptime") cfg.show_uptime = (v == "1");
        else if (k == "show_memory") cfg.show_memory = (v == "1");
        else if (k == "show_load") cfg.show_load = (v == "1");
        else if (k == "show_processes") cfg.show_processes = (v == "1");
        else if (k == "show_audio") cfg.show_audio = (v == "1");
        else if (k == "show_display") cfg.show_display = (v == "1");
        else if (k == "theme") cfg.theme = v;
    }
}
