#pragma once

/**
 * Configuration Features Headers
 * Modular feature toggles for the configuration menu
 */

// GPU Monitoring
void toggleGPUMonitoring();
bool getGPUMonitoringStatus();
const char* getGPUMonitoringLabel();
const char* getGPUMonitoringDescription();

// Disk Monitoring
void toggleDiskMonitoring();
bool getDiskMonitoringStatus();
const char* getDiskMonitoringLabel();
const char* getDiskMonitoringDescription();

// Network Monitoring
void toggleNetworkMonitoring();
bool getNetworkMonitoringStatus();
const char* getNetworkMonitoringLabel();
const char* getNetworkMonitoringDescription();

// Battery Display
void toggleBatteryDisplay();
bool getBatteryDisplayStatus();
const char* getBatteryDisplayLabel();
const char* getBatteryDisplayDescription();

// Weather Display
void toggleWeatherDisplay();
bool getWeatherDisplayStatus();
const char* getWeatherDisplayLabel();
const char* getWeatherDisplayDescription();

// Advanced CPU Info
void toggleAdvancedCPU();
bool getAdvancedCPUStatus();
const char* getAdvancedCPULabel();
const char* getAdvancedCPUDescription();

// Security Information
void toggleSecurityInfo();
bool getSecurityInfoStatus();
const char* getSecurityInfoLabel();
const char* getSecurityInfoDescription();

// Package Count
void togglePackageCount();
bool getPackageCountStatus();
const char* getPackageCountLabel();
const char* getPackageCountDescription();

// Theme Selector
void selectTheme(const std::string& theme_name);
std::string getCurrentTheme();
const char* getThemeSelectorLabel();
const char* getThemeSelectorDescription();
