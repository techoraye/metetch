/**
 * System Information Module - Pure C++ Implementation
 * No shell piping, clean and organized
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <pwd.h>
#include <sys/utsname.h>
#include "modules/system.h"

using namespace std;

namespace sys {

string getUser() {
    uid_t uid = geteuid();
    struct passwd* pw = getpwuid(uid);
    return pw ? string(pw->pw_name) : "Unknown";
}

string getHostname() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        return string(hostname);
    }
    return "Unknown";
}

string getOS() {
    ifstream os_file("/etc/os-release");
    if (os_file.is_open()) {
        string line;
        while (getline(os_file, line)) {
            if (line.find("PRETTY_NAME=") == 0) {
                string os = line.substr(12);
                if (os.front() == '"') os = os.substr(1, os.length() - 2);
                return os;
            }
        }
    }
    return "Unknown OS";
}

string getKernel() {
    struct utsname buf;
    if (uname(&buf) == 0) {
        return string(buf.release);
    }
    return "Unknown";
}

string getUptime() {
    ifstream uptime_file("/proc/uptime");
    if (uptime_file.is_open()) {
        long uptime_secs = 0;
        uptime_file >> uptime_secs;
        uptime_file.close();
        
        long days = uptime_secs / 86400;
        long hours = (uptime_secs % 86400) / 3600;
        long mins = (uptime_secs % 3600) / 60;
        
        return to_string(days) + "d " + to_string(hours) + "h " + to_string(mins) + "m";
    }
    return "Unknown";
}

string getShell() {
    const char* shell = getenv("SHELL");
    if (!shell) return "Unknown";
    
    string shell_str(shell);
    size_t last_slash = shell_str.find_last_of("/");
    return last_slash != string::npos ? shell_str.substr(last_slash + 1) : shell_str;
}

string getTerminal() {
    const char* term = getenv("TERM");
    return term ? string(term) : "Unknown";
}

string getDesktopEnvironment() {
    const char* de = getenv("XDG_CURRENT_DESKTOP");
    if (de) return string(de);
    
    de = getenv("DESKTOP_SESSION");
    return de ? string(de) : "N/A";
}

string getWindowManager() {
    const char* wayland = getenv("WAYLAND_DISPLAY");
    if (wayland) return "Wayland";
    
    const char* display = getenv("DISPLAY");
    if (display) return "X11";
    
    return "Unknown";
}

int getEmergePackageCount() {
    FILE* fp = popen("qlist -I 2>/dev/null | wc -l", "r");
    if (!fp) return 0;
    int count = 0;
    fscanf(fp, "%d", &count);
    pclose(fp);
    return max(0, count);
}

int getFlatpakPackageCount() {
    if (system("command -v flatpak >/dev/null 2>&1") != 0) return 0;
    FILE* fp = popen("flatpak list --app --columns=application 2>/dev/null | tail -n +1 | wc -l", "r");
    if (!fp) return 0;
    int count = 0;
    fscanf(fp, "%d", &count);
    pclose(fp);
    return max(0, count - 1);  // Skip header
}

int getPackageCount() {
    // Try a range of package manager commands to maximize distro coverage
    const vector<string> cmds = {
        "pacman -Qq 2>/dev/null | wc -l",
        "dpkg-query -W -f='${Package}\\n' 2>/dev/null | wc -l",
        "rpm -qa 2>/dev/null | wc -l",
        "apk info 2>/dev/null | wc -l",
        "xbps-query -l 2>/dev/null | wc -l",
        "eopkg list-installed 2>/dev/null | wc -l",
        "pkg list-installed 2>/dev/null | wc -l"
    };

    for (const auto &cmd : cmds) {
        FILE* fp = popen(cmd.c_str(), "r");
        if (!fp) continue;
        int count = 0;
        if (fscanf(fp, "%d", &count) == 1) {
            pclose(fp);
            if (count > 0) return count;
        } else {
            pclose(fp);
            FILE* fp2 = popen(cmd.c_str(), "r");
            if (!fp2) continue;
            int lines = 0;
            char buf[256];
            while (fgets(buf, sizeof(buf), fp2)) lines++;
            pclose(fp2);
            if (lines > 0) return lines;
        }
    }

    return 0;
}

int getProcessCount() {
    ifstream proc_dir("/proc");
    if (proc_dir.is_open()) {
        FILE* fp = popen("ps -e 2>/dev/null | wc -l", "r");
        if (fp) {
            int count;
            if (fscanf(fp, "%d", &count) == 1) {
                pclose(fp);
                return max(0, count - 1);
            }
            pclose(fp);
        }
    }
    return 0;
}

int getThreadCount() {
    FILE* fp = popen("ps -eL 2>/dev/null | wc -l", "r");
    if (fp) {
        int count;
        if (fscanf(fp, "%d", &count) == 1) {
            pclose(fp);
            return max(0, count - 1);
        }
        pclose(fp);
    }
    return 0;
}

} // namespace sys
