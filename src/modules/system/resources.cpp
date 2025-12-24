/**
 * System Module: System Resources & I/O Information
 * Retrieves disk usage, I/O statistics, and filesystem information
 */

#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sys/statvfs.h>
#include "modules/system/resources.h"

namespace sys_resources {

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

// Get disk total space in MB
long getDiskTotal() {
    struct statvfs st;
    if (statvfs("/", &st) == 0) {
        return (st.f_blocks * st.f_frsize) / 1024 / 1024;
    }
    return 0;
}

// Get disk used space in MB
long getDiskUsed() {
    struct statvfs st;
    if (statvfs("/", &st) == 0) {
        long total = (st.f_blocks * st.f_frsize) / 1024 / 1024;
        long free = (st.f_bfree * st.f_frsize) / 1024 / 1024;
        return total - free;
    }
    return 0;
}

// Get disk free space in MB
long getDiskFree() {
    struct statvfs st;
    if (statvfs("/", &st) == 0) {
        return (st.f_bavail * st.f_frsize) / 1024 / 1024;
    }
    return 0;
}

// Get disk usage percentage
int getDiskPercentage() {
    struct statvfs st;
    if (statvfs("/", &st) == 0) {
        if (st.f_blocks > 0) {
            return ((st.f_blocks - st.f_bfree) * 100) / st.f_blocks;
        }
    }
    return 0;
}

// Get I/O read bytes
long getIOReadBytes() {
    std::string output = executeCommand("cat /proc/diskstats 2>/dev/null | awk '{sum+=$6} END {print sum}'");
    if (!output.empty()) {
        try {
            return std::stol(output) * 512; // sectors to bytes
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

// Get I/O write bytes
long getIOWriteBytes() {
    std::string output = executeCommand("cat /proc/diskstats 2>/dev/null | awk '{sum+=$10} END {print sum}'");
    if (!output.empty()) {
        try {
            return std::stol(output) * 512; // sectors to bytes
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

// Get I/O read operations
long getIOReadOps() {
    std::string output = executeCommand("cat /proc/diskstats 2>/dev/null | awk '{sum+=$1} END {print sum}'");
    if (!output.empty()) {
        try {
            return std::stol(output);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

// Get I/O write operations
long getIOWriteOps() {
    std::string output = executeCommand("cat /proc/diskstats 2>/dev/null | awk '{sum+=$5} END {print sum}'");
    if (!output.empty()) {
        try {
            return std::stol(output);
        } catch (...) {
            return 0;
        }
    }
    return 0;
}

// Get comprehensive resource info
ResourceInfo getResourceInfo() {
    ResourceInfo info;
    info.disk_total = getDiskTotal();
    info.disk_used = getDiskUsed();
    info.disk_free = getDiskFree();
    info.disk_percent_used = getDiskPercentage();
    info.io_read_bytes = getIOReadBytes();
    info.io_write_bytes = getIOWriteBytes();
    info.io_read_ops = getIOReadOps();
    info.io_write_ops = getIOWriteOps();
    
    return info;
}

} // namespace system::resources
