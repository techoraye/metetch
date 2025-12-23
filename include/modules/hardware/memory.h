#pragma once

namespace hardware::memory {
    struct MemoryInfo {
        long used;
        long total;
        long percent;
    };
    
    MemoryInfo get();
}
