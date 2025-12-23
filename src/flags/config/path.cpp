/**
 * Configuration Path Manager
 * Determines and creates the configuration directory
 */

#include <string>
#include <sys/stat.h>
#include <cstdlib>

using namespace std;

string configPath() {
    const char* home = getenv("HOME");
    if (!home) home = ".";
    string dir = string(home) + "/.config/metfetch";
    struct stat st;
    if (stat(dir.c_str(), &st) != 0) mkdir(dir.c_str(), 0700);
    return dir + "/config.ini";
}
