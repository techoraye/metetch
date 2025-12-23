#pragma once
#include <string>
#include <vector>

namespace sys_security {
    struct SecurityInfo {
        std::string selinux_status;
        std::string apparmor_status;
        bool firewall_enabled;
        int running_processes;
        int stopped_processes;
        int total_processes;
        std::string last_login;
        int failed_login_attempts = 0;
        bool sudo_access;
    };
    
    SecurityInfo getSecurityInfo();
    std::string getSELinuxStatus();
    std::string getAppArmorStatus();
    bool isFirewallEnabled();
    int getRunningProcesses();
    int getStoppedProcesses();
    int getTotalProcesses();
    std::string getLastLogin();
    int getFailedLoginAttempts();
    bool hasSudoAccess();
}
