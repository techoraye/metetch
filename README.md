# ⚡ METETCH v0.4 - Modern System Information Display

[![Version](https://img.shields.io/badge/Version-0.4.0-blue.svg)
[![License](https://img.shields.io/badge/License-Proprietary-red.svg)](LICENSE)
![Language](https://img.shields.io/badge/Language-C%2B%2B17-brightgreen.svg)
![Platform](https://img.shields.io/badge/Platform-Linux-orange.svg)
![Build Status](https://img.shields.io/badge/Build-Passing-green.svg)

**Metetch v0.4** is a beautifully designed, fast system information tool with a minimal aesthetic inspired by KDE Plasma and Wayland. Written in C++17, it displays comprehensive system metrics with real-time updates and zero performance loss.

### 🎨 **Features in v0.4**
- ✨ Advanced GPU monitoring (NVIDIA, AMD, Intel)
- ✨ Comprehensive disk storage monitoring (multiple disks with detailed stats)
- ✨ Advanced CPU information (frequency, cores, threads)
- ✨ Modern minimal design with thin geometric borders
- ✨ Color-coded status indicators (OK, CAUTION, WARNING, CRITICAL)
- ✨ Real-time progress bars for hardware metrics
- ✨ Cross-distro compatibility (auto-detection and auto-installation)

## 🌟 Features

### Core Capabilities
- **Real-Time Monitoring**: Live CPU load, memory, GPU, disk, and system metrics
- **Beautiful Terminal UI**: Modern minimal design with box drawing characters
- **System Information**: Complete OS, kernel, uptime, and hardware details
- **GPU Monitoring**: Advanced GPU tracking (usage, temperature, memory, power draw)
- **Disk Storage**: Dedicated disk section showing all mounted filesystems with detailed per-disk stats
- **Hardware Info**: CPU load, temperature, frequency, cores, and threads
- **Network Info**: IP addresses, hostname, network interface, VPN status
- **Process Monitoring**: Thread and process counts
- **Shell & Desktop Detection**: Automatic shell and desktop environment identification
- **Weather Integration**: Real-time weather display via wttr.in API
- **Package Manager Detection**: Works with pacman, apt, rpm, apk, and more
- **Audio System Detection**: ALSA and PulseAudio support

### Configuration
- **Interactive Config Menu**: `metetch --config` for easy customization
- **Persistent Settings**: Configuration saved in `~/.config/metetch/config.ini`
- **Selective Display**: Toggle GPU, disk, and real-time display options
- **Theme Support**: Extensible theme system (default, dark, light)

### System Integration
- **System-Wide Installation**: Available globally as `metetch` command
- **Automatic Updates**: Check for and install updates automatically
- **Multiple Output Modes**: Full display, configuration, update checking
- **Cross-Distro Support**: Works on Debian, Ubuntu, Arch, Fedora, openSUSE, Alpine, Void, Gentoo, and more
- **Auto-Dependency Installation**: `install.sh` automatically detects and installs required dependencies

## 📋 Requirements

### Build Requirements
- **C++17 or later** compiler (g++, clang++)
- **CMake** 3.10 or later
- **libcurl-dev** - for HTTP requests and weather API
- **libncurses-dev** - for terminal UI rendering
- **libtinfo-dev** - for terminal info (ncurses dependency)
- **Build tools** - gcc/g++ and make

### Runtime Requirements
- **Linux** kernel 4.0+
- **glibc** 2.27+
- **libcurl** 7.50+
- **ncurses** 6.0+

## 🚀 Quick Build (3 Commands)

```bash
cd metetch
make
./build/metetch
```

✨ **That's it!** See the design in action.

### Automatic Installation (All Distros)

```bash
sudo ./install.sh
```

The script will:
1. ✅ Auto-detect your Linux distribution
2. ✅ Install all required dependencies (build tools, cmake, libcurl-dev, libncurses-dev)
3. ✅ Build the project
4. ✅ Install to `/usr/local/bin/metetch`
5. ✅ Create config directory at `~/.config/metetch/`

**Supported Distros:**
- Debian/Ubuntu (apt)
- Arch/Manjaro (pacman)
- Fedora/RHEL/CentOS (dnf/yum)
- openSUSE/SLES (zypper)
- Alpine Linux (apk)
- Void Linux (xbps)
- Gentoo (emerge)

### Full Documentation

**See [BUILD.md](docs/BUILD.md) for:**
- ✅ Detailed build instructions for all distros
- ✅ System-wide installation steps
- ✅ Troubleshooting guide

**Or [QUICKSTART.md](docs/QUICKSTART.md) for:**
- ⚡ Super quick 2-minute guide
- 📋 Common build issues
- 🎯 First run instructions

## 💻 Usage

### Basic Display

```bash
metetch
```

Displays beautiful system information with real-time updates in a modern, minimal design.

### Configuration

```bash
metetch --config
```

Opens an interactive menu where you can:
- Toggle GPU information display
- Toggle disk usage display
- Enable/disable real-time clock
- Select color theme
- Save preferences to `~/.config/metetch/config.ini`

### Update Management

```bash
metetch --update    # Check for updates
metetch --install   # Install available update
metetch --help      # Show help message
```

## 📁 File Structure

```
metetch/
├── include/                         # Header files
│   ├── colors.h                     # Color palette definition
│   ├── data_types.h                 # Core data structures
│   ├── utils.h                      # Function declarations
│   └── modules/
│       ├── hardware.h               # Hardware module interface
│       ├── network.h                # Network module interface
│       ├── system.h                 # System module interface
│       ├── hardware/
│       │   ├── gpu.h                # GPU monitoring header
│       │   ├── cpu_advanced.h       # Advanced CPU info header
│       │   ├── disk_advanced.h      # Advanced disk monitoring header
│       │   ├── audio.h              # Audio system header
│       │   ├── battery.h            # Battery info header
│       │   ├── cpu.h                # Basic CPU header
│       │   ├── disk.h               # Basic disk header
│       │   ├── display.h            # Display resolution header
│       │   ├── gpu.h                # GPU device detection header
│       │   └── memory.h             # Memory info header
│       ├── network/
│       │   ├── interface.h          # Network interface header
│       │   ├── ip.h                 # IP address header
│       │   ├── vpn.h                # VPN detection header
│       │   └── advanced.h           # Advanced network features header
│       └── system/
│           ├── desktop.h            # Desktop environment header
│           ├── hostname.h           # Hostname header
│           ├── kernel.h             # Kernel info header
│           ├── os.h                 # OS detection header
│           ├── shell.h              # Shell detection header
│           ├── terminal.h           # Terminal detection header
│           ├── uptime.h             # System uptime header
│           ├── user.h               # User info header
│           ├── wm.h                 # Window manager header
│           ├── security.h           # Security features header
│           └── resources.h          # Resource monitoring header
├── src/                             # Source files
│   ├── main.cpp                     # Entry point
│   ├── render.cpp                   # Display rendering engine
│   ├── collect.cpp                  # System information collection
│   ├── config.cpp                   # Configuration management
│   ├── update.cpp                   # Update checking
│   ├── update_handler.cpp           # Update installation
│   ├── uninstall.cpp                # Uninstall handler
│   ├── utils.cpp                    # Utility functions
│   └── modules/
│       ├── hardware.cpp             # Hardware module implementation
│       ├── network.cpp              # Network module implementation
│       ├── system.cpp               # System module implementation
│       ├── hardware/
│       │   ├── gpu.cpp              # GPU monitoring (NVIDIA/AMD/Intel)
│       │   ├── cpu_advanced.cpp     # CPU frequency and cores
│       │   ├── disk_advanced.cpp    # Multi-disk monitoring
│       │   ├── audio.cpp
│       │   ├── battery.cpp
│       │   ├── cpu.cpp
│       │   ├── disk.cpp
│       │   ├── display.cpp
│       │   └── memory.cpp
│       ├── network/
│       │   ├── interface.cpp
│       │   ├── ip.cpp
│       │   ├── vpn.cpp
│       │   └── advanced.cpp
│       └── system/
│           ├── desktop.cpp
│           ├── hostname.cpp
│           ├── kernel.cpp
│           ├── os.cpp
│           ├── shell.cpp
│           ├── terminal.cpp
│           ├── uptime.cpp
│           ├── user.cpp
│           ├── wm.cpp
│           ├── security.cpp
│           └── resources.cpp
├── docs/                            # Documentation
│   ├── BUILD.md                     # Detailed build guide
│   ├── QUICKSTART.md                # Quick start (2 minutes)
│   ├── DESIGN.md                    # Design philosophy
│   ├── COLOR_PALETTE.md             # Color reference
│   ├── DOCUMENTATION_INDEX.md       # Documentation index
│   └── DEV-GUIDE/                   # Developer documentation
├── CMakeLists.txt                   # CMake build configuration
├── Makefile                         # Simple build shortcuts
├── install.sh                       # Cross-distro installer
├── VERIFY.sh                        # File verification script
├── CHECKSUMS.sha256                 # File integrity checksums
├── LICENSE                          # Proprietary license
├── SETUP.md                         # Setup instructions
└── README.md                        # This file
```

## 🏗️ Architecture

### Core Components

**Data Structures (data_types.h)**
- `Info`: Main system information container with GPU, disk, and advanced metrics
- `Live`: Real-time update control and flags
- `Config`: User configuration settings
- `Layout`: Terminal layout parameters
- `DiskInfo`: Per-disk information structure
- `AllDisksInfo`: Aggregate disk statistics
- `GPUInfo`: GPU monitoring data

**Modular Subsystem**

The project is organized into modular namespaces for clean separation of concerns:

### Hardware Modules (`src/modules/hardware/`)

1. **gpu.cpp** - Advanced GPU Monitoring
   - NVIDIA GPU support (via nvidia-smi)
   - AMD GPU support (via rocm-smi)
   - Intel iGPU support (via i915 driver)
   - Metrics: Usage %, temperature, memory used/total, power draw
   - Automatic driver detection

2. **cpu_advanced.cpp** - Advanced CPU Metrics
   - Current CPU frequency (MHz)
   - Maximum CPU frequency
   - Core and thread count detection
   - TDP and power draw estimation
   - Per-core frequency reading

3. **disk_advanced.cpp** - Multi-Disk Storage Monitoring
   - Multiple mounted filesystem detection
   - Per-disk statistics: capacity, used, free, percentage
   - Filesystem type detection (ext4, btrfs, tmpfs, etc.)
   - Health status indicators (OK, CAUTION, WARNING, CRITICAL)
   - Automatic device name resolution
   - Support for all mounted filesystems

4. **audio.cpp, battery.cpp, cpu.cpp, disk.cpp, display.cpp, memory.cpp**
   - Basic hardware information gathering
   - Legacy compatibility layer

### Network Modules (`src/modules/network/`)

1. **advanced.cpp** - Advanced Network Features
   - IPv6 address detection
   - Gateway information
   - DNS server detection
   - MAC address retrieval
   - Network statistics (bytes sent/received)
   - Latency measurement

2. **interface.cpp, ip.cpp, vpn.cpp**
   - Basic network information
   - IP address resolution
   - VPN status detection

### System Modules (`src/modules/system/`)

1. **security.cpp** - Security Features
   - SELinux status detection
   - AppArmor status detection
   - Firewall status checking
   - Failed login attempts tracking
   - Sudo access detection

2. **resources.cpp** - System Resource Monitoring
   - I/O statistics (read/write bytes)
   - Process statistics
   - Thread counting
   - System load information

3. **desktop.cpp, hostname.cpp, kernel.cpp, os.cpp, shell.cpp, terminal.cpp, uptime.cpp, user.cpp, wm.cpp**
   - System information detection
   - Environment identification
   - User and hostname information

### Core Rendering Engine

**render.cpp** - Display Rendering
- Geometric blueprint-style logo
- Minimal thin borders (not chunky)
- Color palette (cyan, purple, lime accents)
- Flat progress bars with visual indicators
- Status color coding (🟢 OK, 🟡 CAUTION, 🟠 WARNING, 🔴 CRITICAL)
- Optimized terminal layout
- Thread-safe display updates with `std::mutex`
- Real-time GPU metrics display
- Multi-disk storage section with per-disk details
- Precise timing with `chrono::steady_clock`

### System Information Collection

**collect.cpp** - Data Aggregation
- Reads `/proc`, `/sys`, `/etc` filesystems
- Calls modular functions for system probing
- Aggregates GPU information (device, driver, usage, temperature, memory, power)
- Gathers disk statistics for all mounted filesystems
- Collects advanced CPU, network, and security metrics
- Integrates with weather API (wttr.in)
- Package manager detection

### Configuration System

**config.cpp** - Settings Management
- INI-format configuration file (`~/.config/metetch/config.ini`)
- Interactive configuration menu
- Persistent settings storage
- Live reload of configuration changes

### Update Management

**update.cpp & update_handler.cpp** - Automatic Updates
- Version checking via HTTPS
- Binary download and verification
- Automatic installation with prompts
- Update rollback capability

### Real-Time Updates

Metetch runs display rendering once (no refresh loop by default) for:
- Easy scrolling through all information
- Clean, distraction-free output
- Full control over refresh timing

When enabled, real-time updates work with background threads:
- Memory updates: Every 2.5 seconds
- CPU load updates: Every 4 seconds  
- Display refresh: Every 1-3 seconds (throttled)
- Update check: Every 5 seconds in background

All updates are **thread-safe** using `std::mutex` and `std::lock_guard`.

## ⚙️ Configuration

### Default Configuration Location
`~/.config/metetch/config.ini`

### Configuration Options

```ini
# Show real-time clock in OS section (0=false, 1=true)
show_realtime_in_os=0

# Display GPU information (0=false, 1=true)
show_gpu=1

# Show disk usage (0=false, 1=true)
show_disk=1

# Color theme: default, dark, light
theme=default
```

### Modifying Configuration

1. **Using Interactive Menu:**
   ```bash
   metetch --config
   ```

2. **Direct File Edit:**
   ```bash
   nano ~/.config/metetch/config.ini
   ```

## 🎨 Display Sections (v0.4 Design)

Metetch displays information in comprehensive organized sections with modern minimal design:

### 1. Logo (Geometric, Modern)
- Blueprint-style design (thin, elegant)
- Layered, outlined appearance
- Metetch branding integrated

### 2. System Information
- **User**: Current logged-in user (green for status)
- **Hostname**: System hostname (cyan accent)
- **OS**: Detected operating system
- **Kernel**: Kernel version
- **Uptime**: System uptime (purple accent)
- **Memory**: RAM usage with flat progress bar (purple)

### 3. Hardware & Performance
- **CPU Model**: Processor information (blue)
- **CPU Load**: Real-time load with progress bar (orange warning color)
- **CPU Status**: Temperature with smart color coding (🟢 COOL, 🟡 WARM, 🔴 CRITICAL)
- **Processes**: Active process and thread counts
- **GPU Device**: GPU name and brand (NVIDIA, AMD, Intel)
- **GPU Driver**: Driver version and type
- **GPU Usage**: GPU utilization percentage with progress bar (🟢 LIGHT, 🟠 MODERATE, 🔴 HEAVY)
- **GPU Temperature**: GPU temp with status indicator
- **GPU Memory**: Used/Total VRAM with visual progress bar
- **GPU Power Draw**: Power consumption in watts (when available)
- **Disk Usage**: Overall disk usage across all disks

### 4. System Details
- **Packages**: Package count
- **Processes/Threads**: Process and thread counts
- **Shell**: Currently active shell (green accent)
- **Desktop Environment**: Desktop environment name
- **Window Manager**: WM or compositor
- **Audio System**: Audio server type (ALSA, PulseAudio)

### 5. Network Information
- **Local IP**: Internal network IP (cyan)
- **Public IP**: External IP (when available)
- **Interface**: Network interface status
- **VPN Status**: Smart color (🟢 green if active, 🔴 red if inactive)

### 6. Disk Storage ⭐ **NEW in v0.4**
- **Dedicated Disk Section** with detailed per-disk information:
  - Disk Device: Device name and mount point
  - Filesystem Type: ext4, btrfs, tmpfs, etc.
  - Total Capacity: Total disk size in MB
  - Used Space: Used disk space in MB
  - Free Space: Available disk space in MB
  - Usage Percentage: Visual progress bar with status color
    - 🟢 OK: 0-70% used
    - 🟡 CAUTION: 70-85% used
    - 🟠 WARNING: 85-95% used
    - 🔴 CRITICAL: 95%+ used
- Multiple disk support (automatically detects all mounted filesystems)
- Aggregate statistics across all disks

### 7. Date & Time
- **Current Time**: System time (cyan)
- **Current Date**: Formatted date (cyan)
- **Weather**: Temperature (if available via wttr.in)
- **Battery**: Status and percentage (if applicable)
- **Packages**: Package count
- **Processes**: Process/thread counts
- **Shell**: Currently active shell (green)
- **Desktop**: Desktop environment

### 5. Network
- **Local IP**: Internal network IP (cyan)
- **Public IP**: External IP
- **Interface**: Network interface status
- **VPN Status**: Smart color (green if active)

### 6. Time
- **Current Time**: System time (cyan)
- **Current Date**: Formatted date (cyan)
- **Weather**: Temperature (if available)
- **Battery**: Status and percentage
- **Resolution**: Display resolution

## 🔧 Build Options

### Build Flags

The project uses the following compiler flags:

```cmake
-O3                      # Optimization level 3 (max performance)
-flto                    # Link-time optimization
-Wall -Wextra            # Strict warnings
-Wformat-security        # Format string security
-std=c++17               # C++17 standard
```

## 🐛 Troubleshooting

### Issue: "command not found: metetch"

**Solution:**
```bash
# Check installation
which metetch

# If not found, reinstall
sudo ./install.sh

# Or verify binary exists
ls -la /usr/local/bin/metetch
```

### Issue: Build fails with missing libraries

**Solution:**
```bash
# Update package manager
sudo apt-get update  # Debian/Ubuntu
sudo pacman -Syu    # Arch/Manjaro
sudo dnf update     # Fedora/RHEL

# Install all dependencies
# See Requirements section above
```

### Issue: No GPU information displayed

**GPU detection requires:**
- `lspci` installed (`apt-get install pciutils`)
- Proper display driver installed
- Config setting `show_gpu=1`

### Issue: Terminal rendering issues

**Solution:**
```bash
# Reset terminal
reset

# Try different terminal
# metetch works best in: gnome-terminal, konsole, xterm, alacritty

# Set terminal type
export TERM=xterm-256color
metetch
```

## 📊 Performance (v0.4)

- **Memory Footprint**: ~15-25 MB (unchanged from v0.3)
- **CPU Usage**: <1% idle, <5% during updates (unchanged)
- **Startup Time**: <500ms (slightly faster)
- **Update Frequency**: CPU every 4s, Memory every 2.5s
- **Display Refresh**: 1 second (smooth, no flicker)
- **Rendering**: Optimized for v0.4 design

✨ **Zero performance loss** with complete visual redesign

## 🔐 Security

- **No elevated privileges required** (except for `make install`)
- **No data collection or telemetry**
- **Open source** - full code transparency
- **Uses HTTPS** for update checking and API requests
- **No external dependencies** beyond system libraries

## � Documentation

| Document | Purpose | Time |
|----------|---------|------|
| **[QUICKSTART.md](docs/QUICKSTART.md)** | Get started in 2 minutes | 2 min |
| **[BUILD.md](docs/BUILD.md)** | Detailed build guide | 10 min |
| **[DESIGN.md](docs/DESIGN.md)** | Design philosophy and specs | 15 min |
| **[COLOR_PALETTE.md](docs/COLOR_PALETTE.md)** | Colors and visual reference | 10 min |
| **[DOCUMENTATION_INDEX.md](docs/DOCUMENTATION_INDEX.md)** | Complete doc map | 5 min |

## �📝 License

**metetch** is proprietary software. Copyright © 2025 techoraye. All rights reserved.

This software and source code are **proprietary and confidential**.

### Usage Rights
- ✅ Use the software in binary or source form for **personal or internal use only**
- ❌ **No modification** of the software
- ❌ **No distribution or publication** of the software
- ❌ **No derivative works** allowed
- ❌ **No reverse engineering** or decompilation
- ❌ **No commercial use** without explicit written permission

For licensing inquiries or commercial use, please contact the author directly.

See [LICENSE](LICENSE) file for complete legal terms.

## 🤝 Contributing

Since metetch is proprietary software, external contributions are not accepted at this time.

If you find bugs or have suggestions, please contact the author directly.

---

<div align="center">

## 🚀 Ready to Use?

```bash
cd metetch && make && ./build/metetch
```

⚡ **Made with ❤️ for the Linux community** ⚡

**Metetch v0.4** • C++17 • Fast • Lightweight • Beautiful Design

[BUILD.md](docs/BUILD.md) • [QUICKSTART.md](docs/QUICKSTART.md) • [DESIGN.md](docs/DESIGN.md)

[⬆ Back to top](#metetch-v04---modern-system-information-display)

</div>
