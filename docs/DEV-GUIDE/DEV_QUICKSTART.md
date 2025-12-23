# Metetch Developer Quick Start

## For Developers Just Getting Started

### 1. Clone & Build

```bash
cd /home/techoraye/Documents/metetch
mkdir -p build && cd build
cmake ..
make -j$(nproc)
./metetch
```

### 2. Understanding the Codebase (5 min read)

```
metetch/
├── src/main.cpp           ← Start here (10 lines)
├── src/collect.cpp        ← Data gathering
├── src/render.cpp         ← Display formatting
└── src/modules/           ← Feature modules
    ├── hardware/          ← CPU, GPU, memory
    ├── network/           ← Network info
    └── system/            ← System info
```

**Flow**: `main()` → `collect()` → `render()` → Display

### 3. Core Data Structure

```cpp
struct Info {
    string user, host, os, kernel;           // System
    float cpu_load, temp;                    // CPU
    long mem_used, mem_total;                // Memory
    string gpu;                              // GPU
    float gpu_usage, gpu_temp;               // GPU metrics
    string ip, gateway, dns;                 // Network
    // ... many more fields
};
```

### 4. Change the Version (Most Common Task)

**File**: `src/utils.cpp` line 20

```cpp
const string ver = "0.3";  ← Change this
```

Then rebuild:
```bash
make clean && make -j$(nproc)
```

### 5. Add a Simple Feature

**Task**: Add CPU cache size display

**Step 1**: Create module header
```cpp
// include/modules/hardware/cpu_cache.h
namespace hardware::cpu_cache {
    long getL3Cache();  // Returns KB
}
```

**Step 2**: Implement module
```cpp
// src/modules/hardware/cpu_cache.cpp
long getL3Cache() {
    // Read from /proc/cpuinfo or /sys/devices/system/cpu/
    return 8192;  // 8MB example
}
```

**Step 3**: Add to data structure
```cpp
// include/data_types.h - add to Info struct
long cpu_l3_cache = 0;
```

**Step 4**: Collect data
```cpp
// src/collect.cpp - in collect() function
i.cpu_l3_cache = hw::cpu_cache::getL3Cache();
```

**Step 5**: Display data
```cpp
// src/render.cpp - in renderDisplay() function
printRow("L3 Cache", to_string(inf.cpu_l3_cache) + "KB", colors::STATUS_OK);
```

**Step 6**: Build & test
```bash
make && ./metetch
```

### 6. Common Commands

```bash
# Build
cd build && make -j$(nproc)

# Full rebuild
make clean && make -j$(nproc)

# Run
./metetch

# Check version
./metetch --version

# Edit main file
vim ../src/main.cpp

# Find something in code
grep -r "gpu_usage" ..

# Check compilation errors
make 2>&1 | head -20
```

### 7. Key Files Reference

| What | File | Line/Section |
|------|------|--------------|
| Update version | `src/utils.cpp` | 20 |
| Main function | `src/main.cpp` | - |
| Data gathering | `src/collect.cpp` | - |
| Display output | `src/render.cpp` | - |
| Data structures | `include/data_types.h` | - |
| GPU module | `src/modules/hardware/gpu.cpp` | - |
| Network module | `src/modules/network/` | - |

### 8. Module Pattern

All modules follow this pattern:

```cpp
// include/modules/category/name.h
namespace category::name {
    struct Info {
        // data fields
    };
    
    Info getData();
}

// src/modules/category/name.cpp
namespace category::name {
    Info getData() {
        // Read from /proc, /sys, or execute command
        return info;
    }
}
```

### 9. Common Issues

**Issue**: Build fails with "cannot find -lcurl"
```bash
# Install dependencies
sudo pacman -S curl    # Arch
sudo apt install libcurl4-openssl-dev  # Ubuntu
```

**Issue**: GPU info shows "Unknown GPU"
```bash
# Install nvidia-smi or amdgpu
nvidia-smi            # Check if available
lspci | grep -i vga   # List GPUs
```

**Issue**: Can't find output after rebuild
```bash
# Make sure you're running the right binary
./build/metetch       # Correct
./metetch            # Wrong if not in build dir
```

### 10. Making Your First Contribution

1. **Pick a task** (see [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md))
2. **Make changes** following the patterns above
3. **Build & test**: `make && ./metetch`
4. **Check for warnings**: `make 2>&1 | grep -i warning`
5. **Document** changes in comments
6. **Commit**: `git commit -m "[Feature] Description"`

### 11. Navigation Tips

```bash
# Go to build directory
cd build

# Run CMake again (if CMakeLists.txt changed)
cmake .. && make -j$(nproc)

# Go back to source
cd ..

# See file structure
tree -L 2 src/
tree -L 2 include/
```

### 12. Helpful Aliases

Add to your `.bashrc` or `.zshrc`:

```bash
alias metetch-build="cd ~/Documents/metetch/build && make -j$(nproc)"
alias metetch-clean="cd ~/Documents/metetch/build && make clean"
alias metetch-run="~/Documents/metetch/build/metetch"
alias metetch-dev="cd ~/Documents/metetch"
```

### 13. Documentation Files

- **[DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md)** - Complete reference
- **[VERSION_GUIDE.md](VERSION_GUIDE.md)** - Version management
- **[FEATURES_NEW.md](FEATURES_NEW.md)** - New features list
- **[BUILD.md](BUILD.md)** - Build instructions
- **[QUICKSTART.md](QUICKSTART.md)** - User quick start

### 14. Where to Get Help

1. **Code comments** - Most modules have detailed comments
2. **Similar modules** - Copy pattern from existing code
3. **Git history** - See how features were added: `git log --oneline`
4. **Tests** - Build and see output: `./metetch`

### 15. Development Workflow

```bash
1. Start
cd /home/techoraye/Documents/metetch/build

2. Make changes to any src/ or include/ file

3. Rebuild
make -j$(nproc)

4. Test
./metetch

5. If satisfied, commit
cd ..
git add -A
git commit -m "[Category] Description"

6. Next feature
vim src/modules/...
```

---

## Quick Facts

- **Language**: C++17
- **Build**: CMake
- **Main entry**: `src/main.cpp`
- **Data collection**: `src/collect.cpp`
- **Display rendering**: `src/render.cpp`
- **Modules**: `src/modules/` and `include/modules/`
- **Build directory**: `build/`
- **Executable**: `build/metetch`

---

## Next Steps

1. ✅ **Build the project** - Follow section 1
2. ✅ **Read the code** - Start with `src/main.cpp`
3. ✅ **Update version** - Follow section 4
4. ✅ **Add a feature** - Follow section 5
5. ✅ **Read full guide** - See [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md)

---

**Happy coding! 🚀**

For detailed information, see [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md)
