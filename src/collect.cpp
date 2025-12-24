/**
 * Metetch - Information Collection
 * Pure C++ modular collection - zero piping
 */

#include <iostream>
#include <string>
#include <ctime>
#include <sys/sysinfo.h>
#include "data_types.h"
#include "modules/system.h"
#include "modules/hardware.h"
#include "modules/network.h"
#include "modules/hardware/cpu_advanced.h"
#include "modules/network/advanced.h"
#include "modules/system/security.h"
#include "modules/system/resources.h"
#include "utils.h"

using namespace std;
using namespace sys;
using namespace hw;
using namespace net;

void collect(Info& i) {
    i.user = getUser();
    i.host = getHostname();
    i.ip = getLocalIP();
    i.pub_ip = getPublicIP();
    
    // Initialize weather and city defaults
    i.city = "N/A";
    i.weather = "N/A";
    
    // Attempt to resolve city and weather when enabled (in background to not block)
    if (i.pub_ip != "N/A" && cfg.show_weather) {
        string city;
        // Try multiple geolocation APIs
        vector<string> geo_urls = {
            "https://ipinfo.io/" + i.pub_ip + "/json",
            "https://ipapi.co/" + i.pub_ip + "/json/",
            "https://geoip-db.com/json"
        };
        
        for (const auto& geo_url : geo_urls) {
            string js = httpGet(geo_url);
            if (!js.empty()) {
                size_t pos = js.find("\"city\"");
                if (pos != string::npos) {
                    pos = js.find(':', pos);
                    if (pos != string::npos) {
                        size_t q1 = js.find('"', pos);
                        if (q1 != string::npos) {
                            size_t q2 = js.find('"', q1 + 1);
                            if (q2 != string::npos && q2 > q1) {
                                city = js.substr(q1 + 1, q2 - q1 - 1);
                                break;  // Found city, stop trying
                            }
                        }
                    }
                }
            }
        }

        if (!city.empty()) {
            i.city = city;
            // Fetch weather from wttr.in with proper formatting
            string weather_url = "https://wttr.in/" + city + "?format=j1";  // JSON format for better parsing
            string w_json = httpGet(weather_url);
            if (!w_json.empty()) {
                // Simple extraction of current temp/condition
                size_t t_pos = w_json.find("\"temp_C\":");
                if (t_pos != string::npos) {
                    size_t end = w_json.find(',', t_pos);
                    if (end != string::npos) {
                        string temp_str = w_json.substr(t_pos + 9, end - t_pos - 9);
                        // Try description as fallback
                        size_t d_pos = w_json.find("\"description\":");
                        if (d_pos != string::npos) {
                            size_t dq1 = w_json.find('"', d_pos + 14);
                            size_t dq2 = w_json.find('"', dq1 + 1);
                            if (dq1 != string::npos && dq2 != string::npos) {
                                string desc = w_json.substr(dq1 + 1, dq2 - dq1 - 1);
                                i.weather = temp_str + "°C - " + desc;
                            }
                        } else {
                            i.weather = temp_str + "°C";
                        }
                    }
                } else {
                    // Fallback to plain text format if JSON fails
                    string w_plain = httpGet("https://wttr.in/" + city + "?format=1");
                    if (!w_plain.empty()) {
                        while (!w_plain.empty() && (w_plain.back() == '\n' || w_plain.back() == '\r')) w_plain.pop_back();
                        i.weather = w_plain;
                    }
                }
            }
        }
    }
    i.up = getUptime();
    i.up_d = getUptime();
    i.cpu = getCPUModel();
    i.cpu_load = getCPULoad();
    i.temp = getCPUTemperature();
    
    // Collect GPU information using enhanced GPU module
    hardware::gpu::GPUInfo gpu_info = hardware::gpu::getGPUInfo();
    i.gpu = gpu_info.device;
    i.gpu_driver = gpu_info.driver;
    i.gpu_usage = gpu_info.usage;
    i.gpu_temp = gpu_info.temperature;
    i.gpu_mem_used = gpu_info.memory_used;
    i.gpu_mem_total = gpu_info.memory_total;
    i.gpu_power_draw = gpu_info.power_draw;
    
    // Collect advanced CPU information
    hardware::cpu_adv::CPUAdvancedInfo cpu_adv_info = hardware::cpu_adv::getCPUAdvancedInfo();
    i.cpu_freq = cpu_adv_info.current_frequency;
    i.cpu_max_freq = cpu_adv_info.max_frequency;
    i.cpu_cores = cpu_adv_info.core_count;
    i.cpu_threads = cpu_adv_info.thread_count;
    
    // Collect disk information using enhanced disk module
    hardware::disk::AllDisksInfo disk_info = hardware::disk::getAllDisksInfo();
    i.disks = disk_info.disks;
    i.disk_total = disk_info.total_all_mb;
    i.disk_used = disk_info.used_all_mb;
    i.disk_free = disk_info.free_all_mb;
    i.disk_percent = disk_info.percent_used_avg;
    i.disk = getDiskUsage();
    
    i.bat = getBatteryStatus();
    i.res = getDisplayResolution();
    i.os = getOS();
    i.time_r = i.os;
    i.kern = getKernel();
    i.pkgs = getPackageCount();
    i.pkgs_emerge = getEmergePackageCount();
    i.pkgs_flatpak = getFlatpakPackageCount();
    i.processes = getProcessCount();
    i.threads = getThreadCount();
    i.sh = getShell();
    i.de = getDesktopEnvironment();
    i.wm = getWindowManager();
    i.term = getTerminal();
    i.audio_device = getAudioDevice();
    i.net_interface = getNetworkInterface();
    i.vpn_status = getVPNStatus();
    
    struct sysinfo si;
    sysinfo(&si);
    i.mem_used = (si.totalram - si.freeram) * si.mem_unit / 1024 / 1024;
    i.mem_total = si.totalram * si.mem_unit / 1024 / 1024;
    i.mem_percent = (si.totalram > 0) ? ((si.totalram - si.freeram) * 100) / si.totalram : 0;
    i.swap_used = (si.totalswap - si.freeswap) * si.mem_unit / 1024 / 1024;
    i.swap_total = si.totalswap * si.mem_unit / 1024 / 1024;
    
    // legacy defaults already set above
}
