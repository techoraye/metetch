# Metetch Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.4.0] - 2025-12-22

### ✨ Major Features Added

#### Advanced GPU Monitoring
- **NVIDIA GPU Support**: Full metrics via nvidia-smi (usage, temperature, memory, power draw)
- **AMD GPU Support**: Comprehensive monitoring via rocm-smi
- **Intel iGPU Support**: Intel integrated graphics detection and monitoring
- GPU usage percentage with visual progress bars
- GPU temperature with status color indicators (COOL/WARM/CRITICAL)
- GPU memory utilization (used/total) with visual progress
- GPU power draw in watts (when available)
- Automatic GPU driver detection

#### Comprehensive Disk Storage Monitoring ⭐ NEW SECTION
- **Multi-disk Support**: Automatic detection of all mounted filesystems
- **Per-disk Statistics**: Device name, mount point, filesystem type
- **Detailed Metrics**: Total capacity, used space, free space, percentage used
- **Visual Status Indicators**: Progress bars with status colors (OK/CAUTION/WARNING/CRITICAL)
- Health status warnings:
  - 🟢 **OK**: 0-70% used
  - 🟡 **CAUTION**: 70-85% used
  - 🟠 **WARNING**: 85-95% used
  - 🔴 **CRITICAL**: 95%+ used
- Separate dedicated "DISK STORAGE" section in output
- Aggregate statistics across all disks

#### Advanced CPU Information
- Current CPU frequency (MHz)
- Maximum CPU frequency
- Core and thread count detection
- TDP and power draw estimation
- Per-core frequency reading

#### Cross-Distribution Support
- **Auto-Detecting Installer** (`install.sh`):
  - Automatic distro detection (os-release, lsb_release)
  - Auto-installation of dependencies on:
    - Debian/Ubuntu (apt)
    - Arch/Manjaro (pacman)
    - Fedora/RHEL/CentOS (dnf/yum)
    - openSUSE/SLES (zypper)
    - Alpine Linux (apk)
    - Void Linux (xbps)
    - Gentoo (emerge)
  - No manual dependency installation needed
- **Cross-Distro Verification** (`VERIFY.sh`):
  - Multiple SHA256 checksum tools support (sha256sum, shasum, sha256)
  - Works on all major Linux distributions
  - File integrity verification

#### Modular Architecture Refactor
- **Namespaced Modules**:
  - `hardware::gpu` - GPU monitoring
  - `hardware::cpu_adv` - Advanced CPU metrics
  - `hardware::disk` - Disk storage monitoring
  - `net_advanced` - Advanced network features
  - `sys_security` - Security features
  - `sys_resources` - Resource monitoring
- **Clean Separation of Concerns**: Each feature in dedicated namespace
- **Easy to Extend**: Modular design for future additions

#### Additional Features
- **Network Advanced Module**: IPv6, gateway, DNS, MAC address
- **Security Module**: SELinux, AppArmor, firewall, failed logins
- **Resource Module**: I/O statistics, system load
- **Professional Display Design**: Color-coded status indicators throughout
- **Static Display Output**: Single render without auto-refresh for easy scrolling

### 🔧 Architecture Improvements

#### Build System
- CMake configuration with C++17 standard
- Optimization flags: `-O3 -flto` for performance
- Modular source organization
- Automatic dependency detection in installer

#### Code Organization
- `include/modules/` - Organized header structure
  - `hardware/` - GPU, CPU, disk, memory, audio, battery, display
  - `network/` - IP, interface, VPN, advanced features
  - `system/` - OS, kernel, shell, desktop, user, security, resources
- `src/modules/` - Implementation files matching headers
- Clean namespace organization avoiding conflicts

#### Rendering Engine
- Completely refactored `render.cpp`
- Modern minimal terminal design
- Geometric logo with blueprint aesthetic
- Thin borders (not chunky)
- Color palette: cyan, purple, lime accents
- Thread-safe display updates with mutex
- Precise timing with chrono::steady_clock

### 📚 Documentation Updates

#### README.md
- Updated feature list with all new capabilities
- Cross-distro installer instructions
- Comprehensive file structure documentation
- Enhanced architecture section with all modules
- Display sections documentation including new disk storage section

#### BUILD.md
- Complete rewrite with auto-installer emphasis
- Step-by-step manual build instructions for all distros
- Troubleshooting guide
- Performance notes
- Build configuration options

#### QUICKSTART.md
- Updated for new installer
- Local testing instructions
- Per-distro dependency lists

#### New Developer Documentation
- `DEV-GUIDE/DEVELOPER_GUIDE.md` - Complete development setup
- `DEV-GUIDE/VERSION_GUIDE.md` - Version management instructions
- `DEV-GUIDE/DEV_QUICKSTART.md` - Quick dev environment setup
- `DEV-GUIDE/DEVELOPER_INDEX.md` - Dev documentation index

### 🐛 Bug Fixes

- **Fixed GPU Info Not Displaying**: GPU module now properly integrated and compiled
- **Fixed Namespace Collision**: Renamed `system::security` and `system::resources` to avoid conflict with C's `system()` function
- **Fixed Display Borders**: Removed extra right border characters for cleaner output
- **Fixed CMakeLists.txt**: Added all new module source files to compilation
- **Fixed Terminal Rendering**: Cross-distro terminal compatibility improvements
- **Fixed Module Includes**: Proper header includes for namespace visibility

### 💥 Breaking Changes

- **Display Behavior**: Changed from continuous refresh to static single-render for scrolling
- **Disk Display**: Replaced simple disk usage with comprehensive multi-disk section
- **Module Structure**: New modular header organization in `include/modules/`
- **Namespace Changes**: System and resource modules use alternative namespaces

### 🔄 Migration Guide

If upgrading from v0.3:

```bash
# Install new version
sudo ./install.sh

# Or manual update
sudo cp build/metetch /usr/local/bin/metetch

# Config remains compatible
# Old ~/.config/metetch/config.ini still works
```

### 📦 Installation & Verification

#### New Installation Method
```bash
sudo ./install.sh
```

#### Verify Integrity
```bash
./VERIFY.sh
```

### 🚀 Performance

- **Binary Size**: ~130-150 KB (stripped)
- **Memory Usage**: ~15-25 MB during operation
- **Startup Time**: <500ms
- **CPU Usage**: <1% idle, <5% during updates
- **No Performance Loss**: New features optimized

### 🔐 Security & Compatibility

- No elevated privileges required (except binary installation)
- No data collection or telemetry
- Full code transparency
- HTTPS for all external requests
- Cross-distro compatibility verified

### 📋 System Requirements

#### Minimum
- Linux kernel 4.0+
- glibc 2.27+
- CMake 3.10+
- C++17 compiler

#### Optional (For Features)
- nvidia-smi - NVIDIA GPU monitoring
- rocm-smi - AMD GPU monitoring
- lspci - GPU device detection

### 🙏 Contributors & Acknowledgments

- Built with C++17 and modern C++ practices
- Uses libcurl, ncurses, pthreads libraries
- Inspired by KDE Plasma and Wayland aesthetics

---

## [0.3.0] - Previous Version

See git history for earlier versions.

---

## Future Roadmap

### Planned for v0.5.0
- [ ] Network bandwidth monitoring
- [ ] Process-specific monitoring
- [ ] Custom display themes
- [ ] Configuration file validation
- [ ] Update notifications

### Planned for v0.6.0
- [ ] Web UI dashboard
- [ ] Export to JSON/CSV
- [ ] Historical data tracking
- [ ] System event notifications

---

## Support & Issues

For bug reports, feature requests, or questions:
- GitHub Issues: https://github.com/techoraye/metfetch/issues
- Check [BUILD.md](docs/BUILD.md) for troubleshooting
- See [DOCUMENTATION_INDEX.md](docs/DOCUMENTATION_INDEX.md) for complete docs

---

**Made with ❤️ for the Linux community** ⚡
