#pragma once

/**
 * Metetch - System Information Display
 * Core Data Structures
 */

#include <string>
#include <vector>
#include <atomic>
#include "modules/hardware/disk_advanced.h"

// ============================================================================
// SYSTEM INFORMATION DATA
// ============================================================================
struct SystemInfo {
    std::string user;
    std::string hostname;
    std::string os;
    std::string kernel;
    std::string uptime;
    std::string shell;
    std::string terminal;
    std::string desktop_env;
    std::string window_manager;
};

// ============================================================================
// ADVANCED CPU DATA
// ============================================================================
struct CPUAdvancedInfo {
    float current_frequency = 0.0f;
    float max_frequency = 0.0f;
    float base_frequency = 0.0f;
    int core_count = 1;
    int thread_count = 1;
    float tdp = 0.0f;
    float power_draw = 0.0f;
};

// ============================================================================
// HARDWARE DATA
// ============================================================================
struct HardwareInfo {
    std::string cpu_model;
    float cpu_load = 0.0f;
    float cpu_temp = 0.0f;
    long mem_used = 0;
    long mem_total = 0;
    long mem_percent = 0;
    std::string gpu_device;
    std::string gpu_driver;
    float gpu_usage = 0.0f;
    float gpu_temp = 0.0f;
    float gpu_mem_used = 0.0f;
    float gpu_mem_total = 0.0f;
    int gpu_power_draw = 0;
    std::string disk_usage;
    std::string audio_system;
    std::string battery_status;
    std::string display_resolution;
    // Advanced CPU info
    CPUAdvancedInfo cpu_adv;
};

// ============================================================================
// ADVANCED NETWORK DATA
// ============================================================================
struct NetworkAdvancedInfo {
    std::string ipv4;
    std::string ipv6;
    std::string gateway;
    std::string dns;
    std::string mac;
    long bytes_recv = 0;
    long bytes_sent = 0;
    int packet_loss = 0;
    float latency = 0.0f;
};

// ============================================================================
// SECURITY DATA
// ============================================================================
struct SecurityInfo {
    std::string selinux;
    std::string apparmor;
    bool firewall = false;
    int running_processes = 0;
    int stopped_processes = 0;
    std::string last_login;
    int failed_logins = 0;
    bool sudo_access = false;
};

// ============================================================================
// RESOURCE DATA
// ============================================================================
struct ResourceInfo {
    long disk_total = 0;
    long disk_used = 0;
    long disk_free = 0;
    int disk_percent = 0;
    long io_read_bytes = 0;
    long io_write_bytes = 0;
};

// ============================================================================
// NETWORK DATA
// ============================================================================
struct NetworkInfo {
    std::string local_ip;
    std::string public_ip;
    std::string interface;
    std::string vpn_status;
    NetworkAdvancedInfo adv;
};

// ============================================================================
// COMBINED INFO STRUCTURE
// ============================================================================
struct Info {
    SystemInfo sys;
    HardwareInfo hw;
    NetworkInfo net;
    SecurityInfo sec;
    ResourceInfo res_info;
    
    // Disk data
    std::vector<hardware::disk::DiskInfo> disks;
    long disk_total = 0;
    long disk_used = 0;
    long disk_free = 0;
    int disk_percent = 0;
    
    // Legacy compatibility - direct access
    std::string user, host, ip, pub_ip, cpu, gpu, disk, bat, res, os, kern, sh, de, wm, term, weather, city;
    long mem_used, mem_total, mem_percent;
    std::string up, up_d, load, time_r;
    float temp, cpu_load;
    float gpu_usage = 0.0f, gpu_temp = 0.0f, gpu_mem_used = 0.0f, gpu_mem_total = 0.0f;
    int gpu_power_draw = 0;
    // Extended CPU info
    float cpu_freq = 0.0f, cpu_max_freq = 0.0f;
    int cpu_cores = 1, cpu_threads = 1;
    // Extended network info
    std::string ipv6, gateway, dns, mac_addr;
    long bytes_recv = 0, bytes_sent = 0;
    // Security info
    int failed_logins = 0;
    // Resource info
    int pkgs, processes, threads;
    long swap_used, swap_total;
    std::string gpu_driver, audio_device, net_interface, vpn_status;
    std::string uptime;
};

// ============================================================================
// RUNTIME STATE
// ============================================================================
struct Live {
    std::atomic<bool> run{true};
    std::atomic<bool> update_shown{false};
    int mem_r = 0, up_r = 0, time_r = 0, load_r = 0, mem_percent_r = 0;
    int temp_r = 0, disk_r = 0;
    int net_rx_r = 0, net_tx_r = 0;
    unsigned long long net_rx_prev = 0, net_tx_prev = 0;
};

// ============================================================================
// DISPLAY LAYOUT
// ============================================================================
struct Layout {
    int box_left_col = 1;
    int label_col    = 2;
    int value_col    = 21;
    int value_width  = 48;
};

// ============================================================================
// APPLICATION CONFIGURATION
// ============================================================================
struct Config {
    // Display toggles
    bool show_gpu = true;
    bool show_disk = true;
    bool show_network = true;
    bool show_battery = true;
    bool show_weather = false;
    bool show_cpu_advanced = true;
    bool show_security = false;
    bool show_packages = true;
    bool show_uptime = true;
    bool show_memory = true;
    bool show_load = true;
    bool show_processes = true;
    bool show_audio = false;
    bool show_display = true;
    
    // Theme selection
    std::string theme = "default";
};

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================
extern Live lv;
extern Config cfg;
extern Layout lay;
extern const std::string ver;
extern const std::string repo;
extern const std::string api;
extern const std::string bin;
