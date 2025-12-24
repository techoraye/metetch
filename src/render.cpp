#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <cmath>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <sstream>
#include <vector>
#include "data_types.h"
#include "colors.h"
#include "utils.h"

using namespace std;
using namespace colors;

static mutex display_mutex;

// Small helper to create bar with thresholds (use UTF-8 strings)
static string makeBar(int percent, int width = 24) {
    int filled = (percent * width) / 100;
    string s;
    for (int i = 0; i < width; ++i) s += (i < filled) ? "█" : "─";
    return s;
}

// Circle load visualization (7-8 circles)
static string loadCircles(int percent) {
    const vector<string> icons = {"🔵","🔵","🔵","🔵","🟢","🟡","🟠","🔴"};
    int active = (percent * (int)icons.size()) / 100;
    if (active < 1) active = 1;
    string out;
    for (size_t i = 0; i < icons.size(); ++i) {
        out += (int)i < active ? icons[i] : string("⚪");
    }
    return out;
}

// Color selection for percent
static const char* pctColor(int p) {
    if (p < 60) return colors::STATUS_OK; // green
    if (p < 80) return colors::STATUS_WARN; // yellow/orange
    return colors::STATUS_CRIT; // red
}

static void printHeader() {
    // Stylized ASCII logo (compact)
    cout << colors::ACCENT_CYAN
         << "                 _       _       _     \n"
         << "  _ __ ___   ___| |_ ___| |_ ___| |__  \n"
         << " | '_ ` _ \\ / _ \\ __/ _ \\ __/ __| '_ \\ \n"
         << " | | | | | |  __/ ||  __/ || (__| | | |\n"
         << " |_| |_| |_|\\___|\\__\\___|\\__\\___|_| |_|\n"
         << colors::RESET << "\n";

    cout << colors::ACCENT_MAGENTA << "  📦 metetch " << ver << "  |  🐙 github.com/techoraye" << colors::RESET << "\n";
    cout << colors::ACCENT_CYAN << "  ─────────────────────────────────────────────" << colors::RESET << "\n\n";
}

static void printSectionTitle(const string &title) {
    // Produce header: '╭─ Title ' then enough dashes to reach column 44
    const int WIDTH = 44;
    string prefix = "╭─ ";
    string middle = " ";
    int used = (int)prefix.size() + (int)title.size() + (int)middle.size();
    int dashes = WIDTH - used;
    if (dashes < 0) dashes = 0;
    cout << colors::ACCENT_CYAN << prefix << title << middle;
    for (int i = 0; i < dashes; ++i) cout << "─";
    cout << colors::RESET << "\n";
}

// Print a single info line: '│ Label: Value' with label padded to 6 characters
static void printKV(const string &k, const string &v) {
    const int LABW = 6;
    string label = k;
    if ((int)label.size() < LABW) label += string(LABW - label.size(), ' ');
    cout << colors::ACCENT_CYAN << "│ " << colors::RESET << colors::TEXT_LABEL << label << ": "
         << colors::RESET << colors::TEXT_VALUE << v << colors::RESET << "\n";
}

void renderDisplay(const Info &inf) {
    lock_guard<mutex> lock(display_mutex);
    system("clear");
    printHeader();

    printSectionTitle("System");
    string host = !inf.host.empty() ? inf.host : inf.sys.hostname;
    string cpu = !inf.cpu.empty() ? inf.cpu : inf.hw.cpu_model;
    string gpu = !inf.gpu.empty() ? inf.gpu : inf.hw.gpu_device;
    int mem_pct = inf.mem_total > 0 ? (int)((inf.mem_used * 100) / inf.mem_total) : 0;
    int disk_pct = inf.disk_percent;

    printKV("Host", host);
    printKV("CPU", cpu);
    printKV("GPU", gpu);
    cout << "\n";

    string memBar = makeBar(mem_pct, 24);
    cout << colors::ACCENT_CYAN << "│ " << colors::RESET << colors::TEXT_LABEL << "Memory" << ": " << colors::RESET;
    cout << pctColor(mem_pct) << memBar << colors::RESET << " ";
    cout << colors::TEXT_VALUE << to_string(inf.mem_used) << "/" << to_string(inf.mem_total) << "MB ";
    cout << pctColor(mem_pct) << to_string(mem_pct) << "%" << colors::RESET << "\n";

    string diskBar = makeBar(disk_pct, 24);
    cout << colors::ACCENT_CYAN << "│ " << colors::RESET << colors::TEXT_LABEL << "Disk  " << ": " << colors::RESET;
    cout << pctColor(disk_pct) << diskBar << colors::RESET << " ";
    cout << colors::TEXT_VALUE << to_string(inf.disk_used) << "/" << to_string(inf.disk_total) << "MB ";
    cout << pctColor(disk_pct) << to_string(disk_pct) << "%" << colors::RESET << "\n";

    cout << "\n";

    printSectionTitle("OS");
    printKV("OS", !inf.os.empty() ? inf.os : inf.sys.os);
    printKV("Kernel", !inf.kern.empty() ? inf.kern : inf.sys.kernel);
    if (cfg.show_packages) {
        string pkg_str = to_string(inf.pkgs_emerge) + "(" + inf.pkg_manager + ")" + " | " + to_string(inf.pkgs_flatpak) + "(flatpak)"; 
        printKV("Package", pkg_str);
    }
    if (cfg.show_processes) {
        printKV("Processes", to_string(inf.processes) + " (mem: " + to_string(inf.mem_percent) + "%%)");
    }
    printKV("Shell", !inf.sh.empty() ? inf.sh : inf.sys.shell);
    printKV("WM/DE", (!inf.wm.empty() ? inf.wm : inf.sys.window_manager) + "/" + (!inf.de.empty() ? inf.de : inf.sys.desktop_env));
    if (cfg.show_gpu) printKV("GPU Driver", inf.gpu_driver);
    if (cfg.show_audio) printKV("Audio", inf.audio_device);

    cout << "\n";

    // Network
    printSectionTitle("Network");
    if (cfg.show_network) {
        printKV("Local IP", !inf.ip.empty() ? inf.ip : inf.net.local_ip);
        printKV("Public IP", inf.pub_ip);
        printKV("VPN", !inf.vpn_status.empty() ? inf.vpn_status : inf.net.vpn_status);
    }
    if (cfg.show_weather && !inf.weather.empty() && inf.weather != "N/A") {
        printKV("Weather", inf.weather);
    }

    cout << "\n";

    // System Status
    printSectionTitle("Status");
    printKV("Uptime", !inf.uptime.empty() ? inf.uptime : inf.up);
    time_t now = time(nullptr);
    struct tm *t = localtime(&now);
    char timebuf[16];
    strftime(timebuf, sizeof(timebuf), "%H:%M:%S", t);
    printKV("Time", string(timebuf));

    int cpu_pct = (int)std::round(inf.cpu_load);
    // CPU bar (use same style as Disk)
    string cpuBar = makeBar(cpu_pct, 24);
    cout << colors::ACCENT_CYAN << "│ " << colors::RESET << colors::TEXT_LABEL << "CPU   " << ": " << colors::RESET;
    cout << pctColor(cpu_pct) << cpuBar << colors::RESET << " ";
    cout << colors::TEXT_VALUE << to_string(cpu_pct) << "%" << colors::RESET << "\n";

    fflush(stdout);
}

// Minimal (compact) renderer intended to fit a small terminal without scrolling
void renderMinimalDisplay(const Info &inf) {
    lock_guard<mutex> lock(display_mutex);
    system("clear");
    // Small one-screen compact layout
    cout << colors::ACCENT_CYAN << "metetch" << colors::RESET << "  "
         << colors::ACCENT_MAGENTA << "v" << ver << colors::RESET << "\n";
    cout << colors::ACCENT_CYAN << "────────────────────────────────" << colors::RESET << "\n";
    int mem_pct = inf.mem_total > 0 ? (int)((inf.mem_used * 100) / inf.mem_total) : 0;
    int disk_pct = inf.disk_percent;

    // Single-line summary rows
    cout << colors::TEXT_LABEL << "Host:" << colors::RESET << " " << colors::TEXT_VALUE << (!inf.host.empty() ? inf.host : inf.sys.hostname) << colors::RESET << "  ";
    cout << colors::TEXT_LABEL << "OS:" << colors::RESET << " " << colors::TEXT_VALUE << (!inf.os.empty() ? inf.os : inf.sys.os) << colors::RESET << "\n";

    cout << colors::TEXT_LABEL << "CPU:" << colors::RESET << " " << colors::TEXT_VALUE << (!inf.cpu.empty() ? inf.cpu : inf.hw.cpu_model) << colors::RESET << "  ";
    cout << colors::TEXT_LABEL << "MEM:" << colors::RESET << " " << pctColor(mem_pct) << to_string(mem_pct) << "%" << colors::RESET << "  ";
    cout << colors::TEXT_LABEL << "DISK:" << colors::RESET << " " << pctColor(disk_pct) << to_string(disk_pct) << "%" << colors::RESET << "\n";

    cout << colors::TEXT_LABEL << "IP:" << colors::RESET << " " << colors::TEXT_VALUE << (!inf.ip.empty() ? inf.ip : inf.net.local_ip) << colors::RESET << "  ";
    cout << colors::TEXT_LABEL << "Uptime:" << colors::RESET << " " << colors::TEXT_VALUE << (!inf.uptime.empty() ? inf.uptime : inf.up) << colors::RESET << "\n";
    fflush(stdout);
}
    
