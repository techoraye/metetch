/**
 * Hardware Module: Memory
 * Retrieves memory usage statistics
 */

#include <sys/sysinfo.h>
#include "modules/hardware/memory.h"

namespace hardware::memory {

MemoryInfo get() {
    struct sysinfo si;
    if (sysinfo(&si) != 0) {
        return {0, 0, 0};
    }
    
    long total = si.totalram * si.mem_unit / 1024 / 1024;
    long used = (si.totalram - si.freeram) * si.mem_unit / 1024 / 1024;
    long percent = total > 0 ? (used * 100) / total : 0;
    
    return {used, total, percent};
}

} // namespace hardware::memory
