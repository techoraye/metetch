#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <sstream>
#include "data_types.h"
#include "colors.h"
#include "utils.h"
#include "modules/hardware.h"

using namespace std;
using namespace colors;

mutex display_mutex;

// Metetch Modern Geometric Logo - Clean & Symmetric (Open Right)
const char* LOGO[] = {
    "  ╭─ ◇ ───────────────────────────────────────────────────────",
    "  │",
    "  │   ┏━━━━╮        ┏━━━┓ ╭━━━┳━━╮ ┏━━━━╮ ┏━━╮      metetch",
    "  │   ┃     ╰━━━┓   ┃   ┃ │   ┃  ┃ ┃     ┃ ┃  ┃",
    "  │   ┃         ┃   ┃   ┃ │   ┃  ┃ ┃     ┃ ┃  ┃",
    "  │   ┗━━━┓     ┃   ┗━━━┛ │   ┃  ┃ ┗━━━━╯ ┗━━╯",
    "  │       ┃     ┃         │   ┃  ┃",
    "  │   ┗━━━╯     ┃         │   ┃  ┃",
    "  │             ┗━━━━━━━━┛    ┃  ┃",
    "  │",
    "  ╰─ ◇ ───────────────────────────────────────────────────────"
};

// Modern thin border drawing functions
void printTopBorder(int width = 80) {
    printf("  ");
    printf("%s┌", colors::ACCENT_CYAN);
    for (int i = 0; i < width - 2; ++i) printf("─");
    printf("┐%s\n", colors::RESET);
}

void printBottomBorder(int width = 80) {
    printf("  ");
    printf("%s└", colors::ACCENT_CYAN);
    for (int i = 0; i < width - 2; ++i) printf("─");
    printf("┘%s\n", colors::RESET);
}

void printSectionDivider(int width = 80) {
    printf("  ");
    printf("%s├", colors::ACCENT_CYAN);
    for (int i = 0; i < width - 2; ++i) printf("─");
    printf("┤%s\n", colors::RESET);
}

void printSectionHeader(const string& title) {
    printf("  %s│%s  %s%s%s\n",
           colors::ACCENT_CYAN,
           colors::RESET,
           colors::TEXT_LABEL,
           title.c_str(),
           colors::RESET);
}

void printRow(const string& label, const string& value, const string& color = "") {
    string col = color.empty() ? colors::TEXT_VALUE : color;
    
    printf("  %s│%s  %s%-26s%s  %s%s%s\n",
           colors::ACCENT_CYAN,
           colors::RESET,
           colors::TEXT_LABEL,
           label.c_str(),
           colors::RESET,
           col.c_str(),
           value.c_str(),
           colors::RESET);
}

void printProgressRow(const string& label, long current, long total, const string& color = "") {
    string col = color.empty() ? colors::ACCENT_PURPLE : color;
    long percent = total > 0 ? (current * 100 / total) : 0;
    
    // Modern flat progress bar (16 chars)
    string bar = "";
    int filled = (percent * 16) / 100;
    for (int i = 0; i < 16; ++i) {
        if (i < filled) bar += "▸";
        else bar += "▹";
    }
    
    printf("  %s│%s  %s%-26s%s  %s%s%s %3ld%%\n",
           colors::ACCENT_CYAN,
           colors::RESET,
           colors::TEXT_LABEL,
           label.c_str(),
           colors::RESET,
           col.c_str(),
           bar.c_str(),
           colors::RESET,
           percent);
}

void renderDisplay(const Info& inf) {
    lock_guard<mutex> lock(display_mutex);
    system("clear");
    
    printf("\n");
    for (int i = 0; i < 11; ++i) {
        printf("%s%s%s\n", colors::ACCENT_CYAN, LOGO[i], colors::RESET);
    }
    printf("\n");
    
    const int WIDTH = 80;
    
    // ===== SYSTEM INFORMATION =====
    printTopBorder(WIDTH);
    printSectionHeader("SYSTEM INFORMATION");
    printSectionDivider(WIDTH);
    
    printRow("User", inf.user, colors::STATUS_OK);
    printRow("Hostname", inf.host, colors::ACCENT_CYAN);
    printRow("OS", inf.os, colors::TEXT_VALUE);
    printRow("Kernel", inf.kern, colors::TEXT_VALUE);
    printRow("Uptime", inf.up, colors::ACCENT_PURPLE);
    printProgressRow("Memory", inf.mem_used, inf.mem_total, colors::COLOR_MEM);
    if (inf.swap_total > 0) {
        printProgressRow("Swap", inf.swap_used, inf.swap_total, colors::ACCENT_PURPLE);
    }
    printBottomBorder(WIDTH);
    printf("\n");
    
    // ===== HARDWARE & PERFORMANCE =====
    printTopBorder(WIDTH);
    printSectionHeader("HARDWARE & PERFORMANCE");
    printSectionDivider(WIDTH);
    
    printRow("CPU Model", inf.cpu, colors::COLOR_CPU);
    
    // CPU Load with status indicator
    string load_status = inf.cpu_load > 75 ? "🔴 HEAVY" : 
                        inf.cpu_load > 50 ? "🟠 MODERATE" : "🟢 LIGHT";
    string load_color = inf.cpu_load > 75 ? colors::STATUS_CRIT : 
                       inf.cpu_load > 50 ? colors::STATUS_WARN : colors::STATUS_OK;
    string load_str = to_string((int)inf.cpu_load) + "% [" + load_status + "]";
    printProgressRow("CPU Load", (long)inf.cpu_load, 100, load_color);
    
    // CPU Advanced Info (if enabled)
    if (cfg.show_cpu_advanced && inf.cpu_cores > 1) {
        printRow("CPU Cores", to_string(inf.cpu_cores) + " cores / " + to_string(inf.cpu_threads) + " threads", colors::TEXT_VALUE);
        if (inf.cpu_freq > 0.0f) {
            string freq_str = to_string((int)inf.cpu_freq) + " MHz (max: " + to_string((int)inf.cpu_max_freq) + " MHz)";
            printRow("CPU Frequency", freq_str, colors::TEXT_VALUE);
        }
    }
    
    // Process and thread information
    printRow("Processes", to_string(inf.processes) + " active | " + to_string(inf.threads) + " threads", colors::TEXT_VALUE);
    
    if (inf.temp > 0) {
        string temp_str = to_string((int)inf.temp) + "°C";
        string temp_color = inf.temp > 80 ? colors::STATUS_CRIT : 
                           inf.temp > 60 ? colors::STATUS_WARN : colors::STATUS_OK;
        string temp_status = inf.temp > 80 ? "🔴 CRITICAL" : 
                            inf.temp > 60 ? "🟠 WARM" : "🟢 COOL";
        printRow("CPU Status", temp_str + " " + temp_status, temp_color);
    }
    
    if (cfg.show_gpu && inf.gpu != "Unknown GPU" && inf.gpu != "N/A") {
        printSectionDivider(WIDTH);
        printRow("⚡ GPU DEVICE", inf.gpu, colors::COLOR_GPU);
        
        if (inf.gpu_driver != "N/A" && !inf.gpu_driver.empty()) {
            printRow("   GPU Driver", inf.gpu_driver, colors::STATUS_OK);
        }
        
        // GPU Usage
        if (inf.gpu_usage > 0.0f) {
            string gpu_status = inf.gpu_usage > 85 ? "🔴 HEAVY" : 
                               inf.gpu_usage > 50 ? "🟠 MODERATE" : "🟢 LIGHT";
            string gpu_color = inf.gpu_usage > 85 ? colors::STATUS_CRIT : 
                              inf.gpu_usage > 50 ? colors::STATUS_WARN : colors::STATUS_OK;
            printProgressRow("   GPU Usage", (long)inf.gpu_usage, 100, gpu_color);
        }
        
        // GPU Temperature
        if (inf.gpu_temp > 0.0f) {
            string gpu_temp_str = to_string((int)inf.gpu_temp) + "°C";
            string gpu_temp_color = inf.gpu_temp > 85 ? colors::STATUS_CRIT : 
                                   inf.gpu_temp > 70 ? colors::STATUS_WARN : colors::STATUS_OK;
            string gpu_temp_status = inf.gpu_temp > 85 ? "🔴 CRITICAL" : 
                                    inf.gpu_temp > 70 ? "🟠 WARM" : "🟢 COOL";
            printRow("   GPU Temp", gpu_temp_str + " " + gpu_temp_status, gpu_temp_color);
        }
        
        // GPU Memory
        if (inf.gpu_mem_total > 0.0f) {
            string gpu_mem_str = to_string((int)inf.gpu_mem_used) + "MB / " + 
                                to_string((int)inf.gpu_mem_total) + "MB";
            float gpu_mem_percent = (inf.gpu_mem_used / inf.gpu_mem_total) * 100.0f;
            string gpu_mem_color = gpu_mem_percent > 85 ? colors::STATUS_CRIT : 
                                  gpu_mem_percent > 70 ? colors::STATUS_WARN : colors::STATUS_OK;
            printProgressRow("   GPU Memory", (long)inf.gpu_mem_used, (long)inf.gpu_mem_total, gpu_mem_color);
        }
        
        // GPU Power Draw
        if (inf.gpu_power_draw > 0) {
            string power_str = to_string(inf.gpu_power_draw) + "W";
            string power_color = inf.gpu_power_draw > 250 ? colors::STATUS_CRIT : 
                                inf.gpu_power_draw > 150 ? colors::STATUS_WARN : colors::STATUS_OK;
            printRow("   Power Draw", power_str, power_color);
        }
    }
    
    // Disk Monitoring (if enabled)
    if (cfg.show_disk && !inf.disks.empty()) {
        printSectionDivider(WIDTH);
        const auto& primary_disk = inf.disks[0];
        printProgressRow("Disk Usage", primary_disk.used_mb, primary_disk.total_mb, colors::COLOR_DISK);
    }
    
    printBottomBorder(WIDTH);
    printf("\n");
    
    // ===== SYSTEM DETAILS =====
    printTopBorder(WIDTH);
    printSectionHeader("SYSTEM DETAILS");
    printSectionDivider(WIDTH);
    
    printRow("Packages", to_string(inf.pkgs), colors::TEXT_VALUE);
    printRow("Processes/Threads", to_string(inf.processes) + "/" + to_string(inf.threads), colors::TEXT_VALUE);
    printRow("Shell", inf.sh, colors::STATUS_OK);
    
    if (!inf.de.empty() && inf.de != "N/A") {
        printRow("Desktop Environment", inf.de, colors::TEXT_VALUE);
    }
    
    if (!inf.wm.empty() && inf.wm != "N/A") {
        printRow("Window Manager", inf.wm, colors::TEXT_VALUE);
    }
    
    if (inf.audio_device != "N/A" && !inf.audio_device.empty()) {
        printRow("Audio System", inf.audio_device, colors::TEXT_VALUE);
    }
    
    // Package Count (if enabled)
    if (cfg.show_packages && inf.pkgs > 0) {
        printRow("📦 Packages", to_string(inf.pkgs) + " installed", colors::ACCENT_LIME);
    }
    
    // Battery Display (if enabled)
    if (cfg.show_battery && inf.bat != "N/A" && !inf.bat.empty()) {
        string bat_color = inf.bat.find("100%") != string::npos ? colors::STATUS_OK :
                          inf.bat.find("Charging") != string::npos ? colors::ACCENT_LIME :
                          inf.bat.find("Discharging") != string::npos && inf.bat.find("20%") != string::npos ? colors::STATUS_CRIT :
                          colors::TEXT_VALUE;
        printRow("🔋 Battery Status", inf.bat, bat_color);
    }
    
    if (inf.res != "N/A" && !inf.res.empty()) {
        printRow("Display Resolution", inf.res, colors::TEXT_VALUE);
    }
    
    printBottomBorder(WIDTH);
    printf("\n");
    
    // ===== NETWORK INFORMATION =====
    printTopBorder(WIDTH);
    printSectionHeader("NETWORK INFORMATION");
    printSectionDivider(WIDTH);
    
    printRow("Local IP", inf.ip, colors::COLOR_NET);
    if (inf.pub_ip != "N/A" && !inf.pub_ip.empty()) {
        printRow("Public IP", inf.pub_ip, colors::TEXT_VALUE);
    }
    printRow("Interface", inf.net_interface, colors::TEXT_VALUE);
    
    string vpn_color = inf.vpn_status.find("Active") != string::npos ? colors::STATUS_OK : colors::TEXT_MUTED;
    printRow("VPN Status", inf.vpn_status, vpn_color);
    
    printBottomBorder(WIDTH);
    printf("\n");
    
    // ===== DISK STORAGE =====
    printTopBorder(WIDTH);
    printSectionHeader("DISK STORAGE");
    printSectionDivider(WIDTH);
    
    // Display all disks from the disks vector
    if (!inf.disks.empty()) {
        for (size_t i = 0; i < inf.disks.size(); ++i) {
            const auto& disk = inf.disks[i];
            
            // Device info row
            string disk_label = (i == 0) ? "Disk Device" : "";
            string disk_info = disk.device + " [" + disk.mount_point + "]";
            if (!disk_label.empty()) {
                printRow(disk_label, disk_info, colors::TEXT_VALUE);
            } else {
                printf("  %s%-19s %s%s\n", colors::TEXT_MUTED, " ", disk_info.c_str(), colors::RESET);
            }
            
            // Filesystem type
            printf("  %s├─ Filesystem    : %s%s%s\n", colors::ACCENT_CYAN, colors::TEXT_VALUE, disk.filesystem.c_str(), colors::RESET);
            
            // Storage capacity
            printf("  %s├─ Total         : %s%ld MB%s\n", colors::ACCENT_CYAN, colors::TEXT_VALUE, disk.total_mb, colors::RESET);
            printf("  %s├─ Used          : %s%ld MB%s\n", colors::ACCENT_CYAN, colors::TEXT_VALUE, disk.used_mb, colors::RESET);
            printf("  %s├─ Free          : %s%ld MB%s\n", colors::ACCENT_CYAN, colors::TEXT_VALUE, disk.free_mb, colors::RESET);
            
            // Usage percentage bar
            int bar_width = 30;
            int filled = (disk.percent_used * bar_width) / 100;
            const char* status_color = (disk.status == "CRITICAL") ? colors::STATUS_CRIT :
                                       (disk.status == "WARNING") ? colors::STATUS_WARN :
                                       (disk.status == "CAUTION") ? colors::STATUS_WARN :
                                       colors::STATUS_OK;
            
            printf("  %s└─ Usage (", colors::ACCENT_CYAN);
            printf("%s%d%%%s", status_color, disk.percent_used, colors::RESET);
            printf("%s)  ", colors::ACCENT_CYAN);
            
            printf("%s", status_color);
            for (int j = 0; j < bar_width; ++j) {
                if (j < filled) printf("█");
                else printf("░");
            }
            printf("%s\n", colors::RESET);
            
            // Add spacing between disks except for the last one
            if (i < inf.disks.size() - 1) {
                printf("  %s\n", colors::TEXT_MUTED);
            }
        }
    } else {
        printRow("Status", "No disk information available", colors::STATUS_WARN);
    }
    
    printBottomBorder(WIDTH);
    printf("\n");
    
    // ===== TIME & DATE =====
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    char timebuf[32], datebuf[64];
    strftime(timebuf, sizeof(timebuf), "%H:%M:%S", t);
    strftime(datebuf, sizeof(datebuf), "%a, %b %d, %Y", t);
    
    printTopBorder(WIDTH);
    printSectionHeader("DATE & TIME");
    printSectionDivider(WIDTH);
    
    printRow("Current Time", string(timebuf), colors::ACCENT_CYAN);
    printRow("Current Date", string(datebuf), colors::ACCENT_CYAN);
    
    if (inf.weather != "N/A" && !inf.weather.empty()) {
        printRow("Weather", inf.weather, colors::TEXT_VALUE);
    }
    
    printBottomBorder(WIDTH);
    
    printf("\n  %s⚡ Made with ❤️  by Techoraye %s\n", colors::ACCENT_CYAN, colors::RESET);
    printf("  %s🔗 GitHub: https://github.com/techoraye/metetch %s\n\n", colors::ACCENT_CYAN, colors::RESET);
    fflush(stdout);
}

void doLiveUpdate(Info& inf) {
    auto last_mem_update = chrono::steady_clock::now();
    auto last_cpu_update = chrono::steady_clock::now();
    auto last_render = chrono::steady_clock::now();
    
    while (lv.run) {
        auto now = chrono::steady_clock::now();
        bool should_render = false;
        
        // Update memory every 2500ms to reduce excessive updates
        if (chrono::duration_cast<chrono::milliseconds>(now - last_mem_update).count() >= 2500) {
            struct sysinfo si;
            if (sysinfo(&si) == 0) {
                inf.mem_used = (si.totalram - si.freeram) * si.mem_unit / 1024 / 1024;
                inf.mem_total = si.totalram * si.mem_unit / 1024 / 1024;
                inf.mem_percent = si.totalram > 0 ? ((si.totalram - si.freeram) * 100) / si.totalram : 0;
            }
            last_mem_update = now;
            should_render = true;
        }
        
        // Update CPU every 3 seconds with smart threshold to prevent spam
        if (chrono::duration_cast<chrono::milliseconds>(now - last_cpu_update).count() >= 3000) {
            float cpu = hw::getCPULoad();
            if (abs(cpu - inf.cpu_load) > 0.5f) {
                inf.cpu_load = cpu;
                should_render = true;
            }
            last_cpu_update = now;
        }
        
        // Render only if data changed and enough time passed to prevent spam
        if (should_render && chrono::duration_cast<chrono::milliseconds>(now - last_render).count() >= 1500) {
            renderDisplay(inf);
            last_render = now;
        }
        
        // Sleep for 250ms to reduce CPU usage
        this_thread::sleep_for(chrono::milliseconds(250));
    }
}

void startLiveUpdater(Info& inf) {
    lv.run = true;
    lv.mem_r = 1;
    lv.load_r = 1;
    
    // Render initial display
    renderDisplay(inf);
    
    thread t(doLiveUpdate, ref(inf));
    t.detach();
}
