#pragma once

#include <string>
#include "data_types.h"

// Utility functions
std::string ex(const std::string& cmd);
std::string httpGet(const std::string& url);
bool downloadFile(const std::string& url, const std::string& out);
std::string extractVer(const std::string& json);
bool isNewer(const std::string& cur, const std::string& latest);

// Animated output
void ac(char ch, int d = 400);
void al(const std::string& s, int d = 400);

// Terminal positioning
inline void mv(int r, int c);

// Display helpers
std::string stripAnsi(const std::string& s);
int visibleLen(const std::string& s);
void clrEol();
void writeField(int r, int c, int width, const std::string& text);

// System info collection
void collect(Info& inf);
float getCpuLoad();
std::string getOsInfo();

// Configuration management
std::string configPath();
void loadConfig();
void saveConfig();
void configureMenu();

// Update/Install management
void doUpdate();
void doInstall();
bool checkUpd();
void showInstallMessage();

// Display rendering
void renderDisplay(const Info& inf);
void startLiveUpdater(Info& inf);
