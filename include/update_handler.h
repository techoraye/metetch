#pragma once

#include <string>
#include <atomic>

namespace update_handler {
    /**
     * Check for available updates
     * Returns true if an update is available
     */
    bool checkForUpdate(std::string& latest_version);
    
    /**
     * Show update notification popup
     * Returns true if user wants to install update
     */
    bool showUpdatePopup(const std::string& current_ver, const std::string& latest_ver);
    
    /**
     * Gracefully shutdown metetch for update
     * Cleans up resources and exits
     */
    void gracefulShutdown();
    
    /**
     * Install update by running install script
     */
    bool installUpdate();
    
    /**
     * Check if metetch is running in the background
     */
    bool isMetetchRunning();
    
    /**
     * Kill any running metetch processes
     */
    void killRunningMetetch();
}
