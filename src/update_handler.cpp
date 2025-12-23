/**
 * Update Handler - Automatic Update Detection & Installation
 * Gracefully handles updates without losing session
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <curl/curl.h>
#include <sstream>
#include "update_handler.h"
#include "utils.h"

using namespace std;

namespace update_handler {

// Callback for CURL response
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool checkForUpdate(string& latest_version) {
    try {
        CURL* curl = curl_easy_init();
        if (!curl) return false;
        
        string response;
        const char* url = "https://api.github.com/repos/techoraye/metetch/releases/latest";
        
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "metetch-updater");
        
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        if (res != CURLE_OK) return false;
        
        // Extract version from JSON response
        size_t pos = response.find("\"tag_name\":\"");
        if (pos == string::npos) return false;
        
        size_t start = pos + 12;
        size_t end = response.find("\"", start);
        latest_version = response.substr(start, end - start);
        
        // Remove 'v' prefix if present
        if (!latest_version.empty() && latest_version[0] == 'v') {
            latest_version = latest_version.substr(1);
        }
        
        return true;
    } catch (...) {
        return false;
    }
}

bool showUpdatePopup(const string& current_ver, const string& latest_ver) {
    // Clear screen
    system("clear");
    
    printf("\n");
    printf("  \033[1;36m╔════════════════════════════════════════════════════════════╗\033[0m\n");
    printf("  \033[1;36m║\033[0m          \033[1;33m⚡ METETCH UPDATE AVAILABLE ⚡\033[0m                    \033[1;36m║\033[0m\n");
    printf("  \033[1;36m╠════════════════════════════════════════════════════════════╣\033[0m\n");
    printf("  \033[1;36m║\033[0m                                                        \033[1;36m║\033[0m\n");
    printf("  \033[1;36m║\033[0m  Current Version: \033[38;5;231m%-42s\033[0m\033[1;36m║\033[0m\n", current_ver.c_str());
    printf("  \033[1;36m║\033[0m  Latest Version:  \033[38;5;118m%-42s\033[0m\033[1;36m║\033[0m\n", latest_ver.c_str());
    printf("  \033[1;36m║\033[0m                                                        \033[1;36m║\033[0m\n");
    printf("  \033[1;36m╠════════════════════════════════════════════════════════════╣\033[0m\n");
    printf("  \033[1;36m║\033[0m  A new version of Metetch is available!                 \033[1;36m║\033[0m\n");
    printf("  \033[1;36m║\033[0m  Would you like to update now?                          \033[1;36m║\033[0m\n");
    printf("  \033[1;36m║\033[0m                                                        \033[1;36m║\033[0m\n");
    printf("  \033[1;36m╠════════════════════════════════════════════════════════════╣\033[0m\n");
    printf("  \033[1;36m║\033[0m  [Y] Update now    [N] Continue running    [Q] Quit     \033[1;36m║\033[0m\n");
    printf("  \033[1;36m╚════════════════════════════════════════════════════════════╝\033[0m\n\n");
    
    printf("  \033[1;33mChoice: \033[0m");
    fflush(stdout);
    
    int choice = getchar();
    
    // Clear input buffer
    while (getchar() != '\n');
    
    if (choice == 'Y' || choice == 'y') {
        return true;
    }
    
    return false;
}

void gracefulShutdown() {
    printf("\n  \033[1;33mℹ\033[0m Shutting down Metetch...\n");
    printf("  \033[1;32m✓\033[0m Update will be installed on next run\n");
    sleep(2);
    exit(0);
}

bool installUpdate() {
    printf("\n  \033[1;33mℹ\033[0m Installing update...\n");
    fflush(stdout);
    
    // Kill any running metetch instances
    killRunningMetetch();
    
    // Run install script with sudo
    int ret = system("sudo /home/$(whoami)/metetch/install.sh > /dev/null 2>&1");
    
    if (ret == 0) {
        printf("  \033[1;32m✓\033[0m Update installed successfully!\n");
        printf("  \033[1;33mℹ\033[0m Restarting Metetch...\n");
        sleep(1);
        return true;
    } else {
        printf("  \033[1;31m✗\033[0m Update failed. Please install manually.\n");
        sleep(2);
        return false;
    }
}

bool isMetetchRunning() {
    int ret = system("pgrep -f 'metetch' > /dev/null 2>&1");
    return ret == 0;
}

void killRunningMetetch() {
    printf("  \033[1;33mℹ\033[0m Closing running Metetch instances...\n");
    system("pkill -f 'metetch' 2>/dev/null || true");
    sleep(1);
}

} // namespace update_handler
