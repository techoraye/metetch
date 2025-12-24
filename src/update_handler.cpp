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
#include "colors.h"

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
    printf("  %s╔════════════════════════════════════════════════════════════╗%s\n", colors::BOLD_CYAN, colors::RESET);
    printf("  %s║%s          %s⚡ METETCH UPDATE AVAILABLE ⚡%s                    %s║%s\n", colors::BOLD_CYAN, colors::RESET, colors::BOLD_YELLOW, colors::RESET, colors::BOLD_CYAN, colors::RESET);
    printf("  %s╠════════════════════════════════════════════════════════════╣%s\n", colors::BOLD_CYAN, colors::RESET);
    printf("  %s║%s                                                        %s║%s\n", colors::BOLD_CYAN, colors::RESET, colors::BOLD_CYAN, colors::RESET);
    printf("  %s║%s  Current Version: %s%-42s%s%s║%s\n", colors::BOLD_CYAN, colors::RESET, colors::TEXT_BRIGHT, current_ver.c_str(), colors::RESET, colors::BOLD_CYAN, colors::RESET);
    printf("  %s║%s  Latest Version:  %s%-42s%s%s║%s\n", colors::BOLD_CYAN, colors::RESET, colors::ACCENT_LIME, latest_ver.c_str(), colors::RESET, colors::BOLD_CYAN, colors::RESET);
    printf("  %s║%s                                                        %s║%s\n", colors::BOLD_CYAN, colors::RESET, colors::BOLD_CYAN, colors::RESET);
    printf("  %s╠════════════════════════════════════════════════════════════╣%s\n", colors::BOLD_CYAN, colors::RESET);
    printf("  %s║%s  A new version of Metetch is available!                 %s║%s\n", colors::BOLD_CYAN, colors::RESET, colors::BOLD_CYAN, colors::RESET);
    printf("  %s║%s  Would you like to update now?                          %s║%s\n", colors::BOLD_CYAN, colors::RESET, colors::BOLD_CYAN, colors::RESET);
    printf("  %s║%s                                                        %s║%s\n", colors::BOLD_CYAN, colors::RESET, colors::BOLD_CYAN, colors::RESET);
    printf("  %s╠════════════════════════════════════════════════════════════╣%s\n", colors::BOLD_CYAN, colors::RESET);
    printf("  %s║%s  [Y] Update now    [N] Continue running    [Q] Quit     %s║%s\n", colors::BOLD_CYAN, colors::RESET, colors::BOLD_CYAN, colors::RESET);
    printf("  %s╚════════════════════════════════════════════════════════════╝%s\n\n", colors::BOLD_CYAN, colors::RESET);
    
    printf("  %sChoice: %s", colors::BOLD_YELLOW, colors::RESET);
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
    printf("\n  %sℹ%s Shutting down Metetch...\n", colors::BOLD_YELLOW, colors::RESET);
    printf("  %s✓%s Update will be installed on next run\n", colors::STATUS_OK, colors::RESET);
    sleep(2);
    exit(0);
}

bool installUpdate() {
    printf("\n  %sℹ%s Installing update...\n", colors::BOLD_YELLOW, colors::RESET);
    fflush(stdout);
    
    // Kill any running metetch instances
    killRunningMetetch();
    
    // Run install script with sudo
    int ret = system("sudo /home/$(whoami)/metetch/install.sh > /dev/null 2>&1");
    
    if (ret == 0) {
        printf("  %s✓%s Update installed successfully!\n", colors::STATUS_OK, colors::RESET);
        printf("  %sℹ%s Restarting Metetch...\n", colors::BOLD_YELLOW, colors::RESET);
        sleep(1);
        return true;
    } else {
        printf("  %s✗%s Update failed. Please install manually.\n", colors::STATUS_CRIT, colors::RESET);
        sleep(2);
        return false;
    }
}

bool isMetetchRunning() {
    int ret = system("pgrep -f 'metetch' > /dev/null 2>&1");
    return ret == 0;
}

void killRunningMetetch() {
    printf("  %sℹ%s Closing running Metetch instances...\n", colors::BOLD_YELLOW, colors::RESET);
    system("pkill -f 'metetch' 2>/dev/null || true");
    sleep(1);
}

} // namespace update_handler
