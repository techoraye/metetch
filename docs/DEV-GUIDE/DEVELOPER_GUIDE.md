# Metetch Developer Documentation

## Table of Contents
1. [Project Overview](#project-overview)
2. [Architecture](#architecture)
3. [Building & Compilation](#building--compilation)
4. [Version Management](#version-management)
5. [Code Structure](#code-structure)
6. [Module System](#module-system)
7. [Data Flow](#data-flow)
8. [Adding New Features](#adding-new-features)
9. [Testing & Debugging](#testing--debugging)
10. [Performance Considerations](#performance-considerations)
11. [Contributing Guidelines](#contributing-guidelines)

---

## Project Overview

**Metetch** is a modern system information display utility for Linux written in C++. It provides real-time monitoring of:
- System information (OS, kernel, uptime, shell, etc.)
- Hardware metrics (CPU, GPU, memory, temperature)
- Network information (IP, gateway, DNS, latency)
- Security status (SELinux, AppArmor, firewall)
- Storage and I/O statistics

**Current Version**: 2.0.0+GPU+Advanced+Metrics
**Language**: C++17
**Build System**: CMake
**Platform**: Linux

---

## Architecture

### High-Level Design

```
┌─────────────────────────────────────────────────────────┐
│                   main.cpp (Entry Point)                 │
└──────────────────────┬──────────────────────────────────┘
                       │
        ┌──────────────┼──────────────┐
        │              │              │
        ▼              ▼              ▼
    collect()    render()        update_check()
        │              │              │
        │              │              │
   ┌────▼──────────┬───┴──────────┬──┴──────────┐
   │               │              │             │
   ▼               ▼              ▼             ▼
[Modules]     [Colors]      [Config]      [Utils]
   │
   ├─ Hardware       render.cpp    config.cpp    utils.cpp
   │  ├─ CPU         colors.h      data_types.h
   │  ├─ GPU
   │  ├─ Memory
   │  └─ Temperature
   │
   ├─ Network
   │  ├─ IP Address
   │  ├─ DNS
   │  └─ Network Stats
   │
   └─ System
      ├─ OS Info
      ├─ Security
      └─ Resources
```

### Core Components

| Component | Purpose | Location |
|-----------|---------|----------|
| **main.cpp** | Application entry point, main loop | `src/main.cpp` |
| **collect.cpp** | Information gathering orchestrator | `src/collect.cpp` |
| **render.cpp** | Display formatting and rendering | `src/render.cpp` |
| **utils.cpp** | Global utilities and helpers | `src/utils.cpp` |
| **config.cpp** | Configuration and argument parsing | `src/config.cpp` |
| **data_types.h** | Core data structures | `include/data_types.h` |
| **Modules/** | Specialized information collectors | `src/modules/`, `include/modules/` |

---

## Building & Compilation

### Prerequisites
```bash
# Install build dependencies
sudo pacman -S cmake gcc git                    # Arch Linux
sudo apt install cmake build-essential git      # Debian/Ubuntu
sudo dnf install cmake gcc git                  # Fedora
```

### Build Steps
```bash
cd /home/techoraye/Documents/metetch

# Create build directory
mkdir -p build
cd build

# Configure
cmake ..

# Compile
make -j$(nproc)

# Install (optional)
sudo make install
```

### CMakeLists.txt Structure
The main `CMakeLists.txt` includes:
- C++17 standard requirement
- All source file compilation
- Header file inclusion paths
- Linking with system libraries (pthread, curl)

### Clean Build
```bash
make clean    # Remove object files
rm -rf build/ # Remove entire build directory
```

---

## Version Management

### Current Version Location
**File**: [src/utils.cpp](src/utils.cpp) (Line 20)

```cpp
const string ver = "0.3";
```

### How to Update Version

**Step 1**: Edit `src/utils.cpp`
```cpp
// Change this line:
const string ver = "0.3";

// To your new version:
const string ver = "2.0.0";
```

**Step 2**: Rebuild the project
```bash
cd build
cmake ..
make -j$(nproc)
```

**Step 3**: Verify version
```bash
./metetch --version
# or check in the display output
```

### Version Format Recommendations
- Use **Semantic Versioning**: `MAJOR.MINOR.PATCH`
- Examples: `2.0.0`, `2.1.3`, `3.0.0`
- Optional: Add descriptors like `2.0.0-GPU-enhanced` or `2.0.0+metrics`

### Related Version References
While the main version is in `src/utils.cpp`, these files also reference versions:
- [include/data_types.h](include/data_types.h) - `extern const std::string ver;` declaration
- [src/update_handler.cpp](src/update_handler.cpp) - Uses `ver` for update checking
- [src/update.cpp](src/update.cpp) - Compares local version with latest

---

## Code Structure

### Directory Layout
```
metetch/
├── CMakeLists.txt              # Build configuration
├── include/                    # Header files
│   ├── modules/               # Module headers
│   │   ├── hardware/          # CPU, GPU, memory modules
│   │   ├── network/           # Network info modules
│   │   └── system/            # System info modules
│   ├── colors.h               # Color definitions
│   ├── data_types.h           # Core structures
│   ├── update_handler.h       # Update checking
│   └── utils.h                # Utility functions
├── src/                        # Source files
│   ├── main.cpp               # Entry point
│   ├── collect.cpp            # Data gathering
│   ├── render.cpp             # Display rendering
│   ├── config.cpp             # Configuration
│   ├── utils.cpp              # Utilities
│   ├── update_handler.cpp     # Update handler
│   └── modules/               # Module implementations
├── docs/                       # Documentation
│   ├── FEATURES_NEW.md        # New features guide
│   └── (other docs)
└── build/                      # Build artifacts (after cmake)
```

### Naming Conventions
- **Files**: lowercase with underscores (`cpu_advanced.cpp`)
- **Classes/Structs**: PascalCase (`struct HardwareInfo`)
- **Functions**: camelCase (`getGPUInfo()`)
- **Variables**: snake_case (`gpu_usage`, `mem_total`)
- **Constants**: UPPER_SNAKE_CASE (`COLOR_GPU`, `WIDTH`)
- **Namespaces**: lowercase (`namespace hardware::gpu`)

### Code Style
- Use `namespace` for organization
- Prefer `std::string` over `char*`
- Use modern C++ (C++17 features)
- Comment complex logic
- Keep functions focused and small
- Use `const` for non-mutable parameters

---

## Module System

### Module Organization

Modules are organized by category:

#### Hardware Modules (`src/modules/hardware/`)
```
hardware/
├── cpu.cpp                  # Basic CPU info
├── cpu_advanced.cpp         # Frequency, TDP, cores
├── gpu.cpp                  # GPU device, driver, usage
├── memory.cpp               # RAM usage
├── temperature.cpp          # CPU temperature
├── disk.cpp                 # Disk space
├── battery.cpp              # Battery status
├── audio.cpp                # Audio system
└── display.cpp              # Display resolution
```

#### Network Modules (`src/modules/network/`)
```
network/
├── ip.cpp                   # IP address detection
├── interface.cpp            # Network interface info
├── advanced.cpp             # IPv6, gateway, DNS, latency
└── vpn.cpp                  # VPN status
```

#### System Modules (`src/modules/system/`)
```
system/
├── os.cpp                   # OS identification
├── kernel.cpp               # Kernel version
├── uptime.cpp               # System uptime
├── shell.cpp                # Current shell
├── terminal.cpp             # Terminal emulator
├── desktop.cpp              # Desktop environment
├── wm.cpp                   # Window manager
├── user.cpp                 # User info
├── hostname.cpp             # Hostname
├── security.cpp             # SELinux, AppArmor, firewall
└── resources.cpp            # Disk I/O statistics
```

### Creating a New Module

**Example: Adding a new `power` module**

**Step 1**: Create header file `include/modules/hardware/power.h`
```cpp
#pragma once
#include <string>

namespace hardware::power {
    struct PowerInfo {
        float voltage;
        float current;
        float power_w;
    };
    
    PowerInfo getPowerInfo();
    float getVoltage();
    float getCurrent();
}
```

**Step 2**: Create implementation `src/modules/hardware/power.cpp`
```cpp
#include <string>
#include <fstream>
#include "modules/hardware/power.h"

namespace hardware::power {

PowerInfo getPowerInfo() {
    PowerInfo info;
    info.voltage = getVoltage();
    info.current = getCurrent();
    info.power_w = info.voltage * info.current;
    return info;
}

float getVoltage() {
    // Implementation
    return 12.0f;
}

float getCurrent() {
    // Implementation
    return 5.0f;
}

}
```

**Step 3**: Update main hardware module header `include/modules/hardware.h`
```cpp
#include "modules/hardware/power.h"  // Add this

// Use in your code:
// hw::power::PowerInfo pwr = hw::power::getPowerInfo();
```

**Step 4**: Update [src/collect.cpp](src/collect.cpp)
```cpp
// Add to collect() function
hw::power::PowerInfo power_info = hw::power::getPowerInfo();
i.power_voltage = power_info.voltage;
i.power_current = power_info.current;
```

**Step 5**: Update [src/render.cpp](src/render.cpp)
```cpp
// Add to renderDisplay() function
if (inf.power_voltage > 0) {
    printRow("Power", to_string(inf.power_w) + "W", colors::STATUS_OK);
}
```

---

## Data Flow

### Information Collection Flow

```
┌─ collect() ────────────────────────────────────────────┐
│                                                         │
│  1. System Info ──┐                                    │
│  2. Hardware  ────┼─> Info struct ─> render()         │
│  3. Network   ────┤                                    │
│  4. Security  ────┤                                    │
│  5. Resources ────┘                                    │
│                                                         │
│  Each module returns specific data structure           │
│  All data is consolidated into main Info struct       │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

### Typical Collection Sequence

1. **System Info** (fast, file-based)
   - User, hostname, OS, kernel
   - Shell, terminal, desktop environment

2. **Hardware** (moderate speed, may exec tools)
   - CPU model, load, temperature
   - GPU info (may call nvidia-smi)
   - Memory usage (sysinfo syscall)
   - Disk, battery, display

3. **Network** (slow, may involve network calls)
   - Local IP (reads /proc/net)
   - Gateway, DNS (reads system config)
   - May ping for latency (timeout)

4. **Advanced Info** (optional, can be slow)
   - Security checks (reads logs)
   - I/O statistics
   - Extended network info

### Optimization Tips

```cpp
// GOOD - Local file read (fast)
std::ifstream file("/proc/cpuinfo");

// SLOW - External command execution
std::string result = executeCommand("lscpu");

// VERY SLOW - Network operation
std::string latency = executeCommand("ping -c 1 8.8.8.8");

// GOOD - Caching for repeated calls
static float cached_freq = 0.0f;
if (cached_freq == 0.0f) {
    cached_freq = getFrequency(); // Only called once
}
return cached_freq;
```

---

## Adding New Features

### Feature: CPU Cache Information

**Design Phase**:
1. Decide data structure
2. Choose data source
3. Plan integration points

**Implementation**:

**1. Create module header** `include/modules/hardware/cpu_cache.h`
```cpp
#pragma once
#include <string>

namespace hardware::cpu_cache {
    struct CacheInfo {
        long l1_cache_kb;
        long l2_cache_kb;
        long l3_cache_kb;
    };
    
    CacheInfo getCacheInfo();
}
```

**2. Implement module** `src/modules/hardware/cpu_cache.cpp`
```cpp
#include "modules/hardware/cpu_cache.h"
#include <fstream>
#include <cstdlib>

namespace hardware::cpu_cache {

CacheInfo getCacheInfo() {
    CacheInfo info = {0, 0, 0};
    
    // Read from /proc/cpuinfo
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    
    while (std::getline(cpuinfo, line)) {
        if (line.find("cache size") != std::string::npos) {
            // Parse and store
        }
    }
    
    return info;
}

}
```

**3. Update data structures** `include/data_types.h`
```cpp
struct HardwareInfo {
    // ... existing fields ...
    long cpu_l1_cache = 0;
    long cpu_l2_cache = 0;
    long cpu_l3_cache = 0;
};

struct Info {
    // ... existing fields ...
    long cpu_l1 = 0, cpu_l2 = 0, cpu_l3 = 0;
};
```

**4. Update collection** `src/collect.cpp`
```cpp
// Add includes
#include "modules/hardware/cpu_cache.h"

// In collect() function
hw::cpu_cache::CacheInfo cache = hw::cpu_cache::getCacheInfo();
i.cpu_l1 = cache.l1_cache_kb;
i.cpu_l2 = cache.l2_cache_kb;
i.cpu_l3 = cache.l3_cache_kb;
```

**5. Update rendering** `src/render.cpp`
```cpp
// In renderDisplay() function
if (inf.cpu_l3 > 0) {
    string cache_str = to_string(inf.cpu_l3) + "KB";
    printRow("   L3 Cache", cache_str, colors::STATUS_OK);
}
```

**6. Update documentation** Update [docs/FEATURES_NEW.md](docs/FEATURES_NEW.md)

**7. Test**
```bash
cd build && make
./metetch
# Verify L3 Cache appears in output
```

---

## Testing & Debugging

### Debug Compilation

Add debug flags to CMakeLists.txt:
```cmake
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -DDEBUG")
```

### Common Issues & Solutions

#### Issue: GPU not detected
```bash
# Check nvidia-smi availability
which nvidia-smi
nvidia-smi --query-gpu=name --format=csv,noheader

# Debug GPU detection
gdb ./metetch
> b gpu.cpp:50
> run
> print output
```

#### Issue: Temperature showing 0
```bash
# Check CPU temp file accessibility
cat /sys/class/thermal/thermal_zone0/temp
# Should show value like 45000 (45°C)
```

#### Issue: Memory calculation wrong
```cpp
// Debug memory info
struct sysinfo si;
sysinfo(&si);
printf("Total: %ld, Free: %ld, Unit: %ld\n", 
    si.totalram, si.freeram, si.mem_unit);
```

### Logging

Add debug output:
```cpp
#ifdef DEBUG
    fprintf(stderr, "[DEBUG] GPU Device: %s\n", device.c_str());
#endif
```

### Performance Profiling

```bash
# Time command execution
time ./metetch

# Profile with valgrind (if installed)
valgrind --tool=callgrind ./metetch
kcachegrind callgrind.out.XXXXX
```

---

## Performance Considerations

### Speed Optimization Strategies

1. **Avoid External Commands**
   ```cpp
   // ❌ SLOW: Spawns process
   std::string result = executeCommand("lscpu");
   
   // ✅ FAST: Direct file read
   std::ifstream file("/proc/cpuinfo");
   ```

2. **Cache Expensive Operations**
   ```cpp
   static std::string cached_value = "";
   if (cached_value.empty()) {
       cached_value = getExpensiveValue();
   }
   return cached_value;
   ```

3. **Use Fast System Calls**
   ```cpp
   // ✅ FAST: System call
   struct sysinfo si;
   sysinfo(&si);
   
   // ❌ SLOW: Parse /proc/meminfo
   ```

4. **Parallel Data Collection**
   ```cpp
   // Collect independent data in parallel
   std::thread t1(collectHardware, std::ref(info));
   std::thread t2(collectNetwork, std::ref(info));
   t1.join();
   t2.join();
   ```

### Memory Efficiency

- Use `const` references for large objects
- Avoid unnecessary string copies
- Use `std::move()` for temporary objects
- Clear containers after use if very large

### Current Performance Targets
- CPU info collection: < 50ms
- GPU info collection: < 100ms (depends on nvidia-smi)
- Network info: < 200ms (if includes ping)
- Total display update: < 500ms

---

## Contributing Guidelines

### Code Review Checklist

Before submitting changes:

- [ ] Follows naming conventions
- [ ] Uses C++17 features appropriately
- [ ] Includes error handling
- [ ] Has meaningful comments for complex logic
- [ ] Builds without warnings: `cmake .. && make`
- [ ] Tested on actual hardware
- [ ] Documentation updated
- [ ] Version number considered for update

### Commit Message Format

```
[Category] Brief description

Longer explanation of changes:
- Point 1
- Point 2

Fixes #123
```

**Categories**:
- `[Feature]` - New functionality
- `[Fix]` - Bug fixes
- `[Docs]` - Documentation updates
- `[Refactor]` - Code improvements
- `[Perf]` - Performance improvements

### Pull Request Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] New feature
- [ ] Bug fix
- [ ] Documentation update

## Testing
Tested on:
- [ ] Arch Linux
- [ ] Ubuntu
- [ ] Fedora
- [ ] Other: ___

## Checklist
- [ ] Builds without errors
- [ ] No compiler warnings
- [ ] Documentation updated
- [ ] Version bumped (if applicable)
```

---

## Architecture Patterns Used

### 1. **Module Pattern**
Each hardware/network/system component is its own module with:
- Header file with function declarations
- Implementation file with logic
- Namespace for organization

### 2. **Data Structure Pattern**
Information flows through well-defined structs:
- Specialized structs for each category (CPUAdvancedInfo, GPUInfo)
- Unified Info struct that contains everything

### 3. **Singleton Pattern**
Global instances:
```cpp
extern Live lv;          // Runtime state
extern Config cfg;       // Configuration
extern Layout lay;       // Display layout
extern const string ver; // Version
```

### 4. **Observer Pattern** (potential)
Could be extended to notify modules of config changes

---

## File Dependency Graph

```
main.cpp
  ├─ collect.cpp
  │   ├─ modules/system.h
  │   ├─ modules/hardware.h
  │   │   ├─ modules/hardware/cpu.h
  │   │   ├─ modules/hardware/gpu.h
  │   │   ├─ modules/hardware/cpu_advanced.h
  │   │   └─ ...
  │   ├─ modules/network.h
  │   │   ├─ modules/network/ip.h
  │   │   ├─ modules/network/advanced.h
  │   │   └─ ...
  │   └─ data_types.h
  │
  ├─ render.cpp
  │   ├─ colors.h
  │   ├─ data_types.h
  │   └─ utils.h
  │
  ├─ config.cpp
  │   └─ data_types.h
  │
  └─ update_handler.cpp
      ├─ data_types.h
      └─ utils.h
```

---

## Quick Reference

### Useful Directories
| Path | Purpose |
|------|---------|
| `src/` | Source implementations |
| `include/` | Header files |
| `build/` | Build artifacts |
| `docs/` | Documentation |
| `src/modules/` | Feature modules |

### Key Files to Modify

| Task | File | Line |
|------|------|------|
| Update version | `src/utils.cpp` | 20 |
| Add GPU feature | `src/modules/hardware/gpu.cpp` | - |
| Change display | `src/render.cpp` | - |
| Add data fields | `include/data_types.h` | - |
| Collect new data | `src/collect.cpp` | - |

### Build Commands
```bash
cmake ..                    # Configure
make -j$(nproc)            # Compile
make clean                 # Clean object files
rm -rf build/              # Full clean
./metetch                  # Run
./metetch --version        # Check version
```

---

## Contact & Support

For questions about development:
- Check existing documentation in `docs/`
- Review similar modules for patterns
- Check GitHub issues for discussions
- Refer to inline code comments

---

**Last Updated**: December 2024
**Documentation Version**: 1.0
**For Metetch Version**: 2.0.0+
