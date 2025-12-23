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
    
    i.weather = "N/A";
    i.city = "N/A";
}
