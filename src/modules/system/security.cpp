/**
 * System Module: Security & Process Information
 * Retrieves security-related information and process statistics
 */

#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "modules/system/security.h"

namespace sys_security {

// Helper to execute commands
std::string executeCommand(const std::string& cmd) {
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";
    
    std::string result;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

// Get SELinux status
std::string getSELinuxStatus() {
    std::string output = executeCommand("getenforce 2>/dev/null");
    if (output.empty()) return "Disabled";
    if (output.back() == '\n') output.pop_back();
    return output;
}

// Get AppArmor status
std::string getAppArmorStatus() {
    std::string output = executeCommand("aa-status 2>/dev/null | head -1");
    if (output.empty()) return "Disabled";
    if (output.back() == '\n') output.pop_back();
    if (output.find("enabled") != std::string::npos) {
        return "Enabled";
    }
    return "Disabled";
}

// Check if firewall is enabled
bool isFirewallEnabled() {
    std::string output = executeCommand("sudo ufw status 2>/dev/null | grep 'Status:' | awk '{print $NF}'");
    if (output.empty()) {
        output = executeCommand("sudo systemctl is-active firewalld 2>/dev/null");
        return !output.empty() && output.find("active") != std::string::npos;
    }
    return output.find("active") != std::string::npos;
}

// Get running processes count
int getRunningProcesses() {
    std::string output = executeCommand("ps aux --no-headers 2>/dev/null | wc -l");
    if (!output.empty()) {
        try {
            return std::stoi(output) - 1; // Subtract ps command itself
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

// Get stopped processes count
int getStoppedProcesses() {
    std::string output = executeCommand("ps aux --no-headers 2>/dev/null | grep defunct | wc -l");
    if (!output.empty()) {
        try {
            return std::stoi(output);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

// Get total processes count
int getTotalProcesses() {
    std::string output = executeCommand("cat /proc/sys/kernel/pid_max 2>/dev/null");
    if (!output.empty()) {
        try {
            return std::stoi(output);
        } catch (...) {
            return 32768; // Default
        }
    }
    return 32768;
}

// Get last login information
std::string getLastLogin() {
    std::string output = executeCommand("lastlog -t 1d 2>/dev/null | head -2 | tail -1 | awk '{print $1, $4, $5, $6, $7}'");
    if (output.empty()) {
        return "N/A";
    }
    if (output.back() == '\n') output.pop_back();
    return output;
}

// Get failed login attempts
int getFailedLoginAttempts() {
    std::string output = executeCommand("grep 'Failed password' /var/log/auth.log 2>/dev/null | wc -l");
    if (!output.empty()) {
        try {
            return std::stoi(output);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

// Check if user has sudo access
bool hasSudoAccess() {
    std::string output = executeCommand("sudo -n id 2>&1");
    return output.find("uid=") != std::string::npos;
}

// Get comprehensive security info
SecurityInfo getSecurityInfo() {
    SecurityInfo info;
    info.selinux_status = getSELinuxStatus();
    info.apparmor_status = getAppArmorStatus();
    info.firewall_enabled = isFirewallEnabled();
    info.running_processes = getRunningProcesses();
    info.stopped_processes = getStoppedProcesses();
    info.total_processes = getTotalProcesses();
    info.last_login = getLastLogin();
    info.failed_login_attempts = getFailedLoginAttempts();
    info.sudo_access = hasSudoAccess();
    
    return info;
}

} // namespace system::security
