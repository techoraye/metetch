# Release Notes - Metetch v0.4.0

## 🎉 Major Release: Complete System Monitor Rewrite

**Release Date:** December 22, 2025  
**Version:** 0.4.0  
**Status:** Stable ✅

---

## 🌟 What's New in v0.4.0

### ⚡ Advanced GPU Monitoring
Full GPU support with comprehensive metrics:
- **NVIDIA**: Usage %, temperature, memory, power draw
- **AMD**: Complete rocm-smi integration
- **Intel**: iGPU support detection
- Visual progress bars and status indicators

### 💾 Dedicated Disk Storage Section (NEW)
Comprehensive multi-disk monitoring:
- Automatic detection of all mounted filesystems
- Per-disk details: device, mount point, filesystem type, capacity
- Color-coded health status (OK → CAUTION → WARNING → CRITICAL)
- Separate display section with detailed statistics

### 🚀 Advanced CPU Information
- Current & maximum CPU frequency
- Core and thread count
- TDP and power draw estimation

### 🔧 Auto-Installing on All Linux Distros
Single command installation that works everywhere:
```bash
sudo ./install.sh
```
Works on: Debian, Ubuntu, Arch, Fedora, openSUSE, Alpine, Void, Gentoo, and more!

### 🛡️ File Verification & Security
Cross-distro verification script:
```bash
./VERIFY.sh
```

---

## 📊 Key Improvements

### Display & User Experience
- ✅ Modern minimal terminal design
- ✅ Color-coded status indicators (🟢 OK, 🟡 CAUTION, 🟠 WARNING, 🔴 CRITICAL)
- ✅ Static display for easy scrolling (no auto-refresh)
- ✅ Professional geometric logo design
- ✅ Thin elegant borders (not chunky)

### Architecture & Code
- ✅ Complete modular refactor with namespaced modules
- ✅ Clean separation: hardware, network, system namespaces
- ✅ Enhanced rendering engine with thread-safe updates
- ✅ Optimized compiler flags (-O3 -flto)
- ✅ Bug fixes for GPU display and terminal rendering

### Documentation
- ✅ Updated README with all new features
- ✅ Comprehensive BUILD.md with all distros
- ✅ Developer documentation (DEV-GUIDE/)
- ✅ CHANGELOG.md with detailed release notes
- ✅ Installation & verification guides

---

## 🚀 Quick Start

### Install (Automatic - All Distros)
```bash
git clone https://github.com/techoraye/metfetch.git
cd metfetch
sudo ./install.sh
```

### Run
```bash
metetch
```

### Verify
```bash
./VERIFY.sh
```

---

## 📋 System Requirements

### Minimum
- Linux kernel 4.0+
- C++17 compiler
- CMake 3.10+

### Build Dependencies (Auto-Installed)
- gcc/g++, make
- cmake
- libcurl-dev
- libncurses-dev

### Optional (For GPU Monitoring)
- nvidia-smi (NVIDIA GPUs)
- rocm-smi (AMD GPUs)
- lspci (GPU detection)

---

## 🔄 Breaking Changes from v0.3

1. **Display Output**: Changed from continuous refresh to static display
2. **Disk Monitoring**: Replaced simple usage with comprehensive multi-disk section
3. **Module Structure**: New header organization in `include/modules/`
4. **Namespace Names**: System and resource modules use alternative names

**Migration**: Config files remain compatible. Just run `sudo ./install.sh`.

---

## 📈 Performance

- **Binary Size**: ~130-150 KB
- **Memory**: ~15-25 MB
- **Startup**: <500ms
- **CPU Usage**: <1% idle
- **Zero Performance Loss**: All features optimized

---

## 🐛 Bug Fixes

- Fixed GPU info not displaying (now properly compiled)
- Fixed namespace collisions with system() function
- Fixed display border rendering issues
- Fixed CMakeLists.txt missing modules
- Fixed terminal compatibility across distros

---

## 📚 Documentation

| Document | Purpose |
|----------|---------|
| **README.md** | Project overview and features |
| **[BUILD.md](docs/BUILD.md)** | Detailed build guide |
| **[QUICKSTART.md](docs/QUICKSTART.md)** | 2-minute quick start |
| **[CHANGELOG.md](CHANGELOG.md)** | Complete version history |
| **[DESIGN.md](docs/DESIGN.md)** | Design philosophy |
| **[COLOR_PALETTE.md](docs/COLOR_PALETTE.md)** | Color reference |
| **[DOCUMENTATION_INDEX.md](docs/DOCUMENTATION_INDEX.md)** | Full documentation map |
| **[DEV-GUIDE/](docs/DEV-GUIDE/)** | Developer documentation |

---

## 🔐 Security & Privacy

- ✅ No data collection or telemetry
- ✅ No elevated privileges required (except install)
- ✅ Full source code transparency
- ✅ HTTPS for all external requests
- ✅ Open source for community review

---

## 🤝 Contributing & Support

- **GitHub Issues**: Report bugs or request features
- **Discussions**: Ask questions and share ideas
- **Documentation**: See [DOCUMENTATION_INDEX.md](docs/DOCUMENTATION_INDEX.md)
- **License**: MIT (See [LICENSE](LICENSE))

---

## 🙏 Acknowledgments

- Built with modern C++17
- Uses libcurl, ncurses, pthreads
- Inspired by KDE Plasma and Wayland
- Made with ❤️ for the Linux community

---

## 📝 License

Metetch is released under the MIT License. See [LICENSE](LICENSE) for details.

**⚡ Metetch v0.4.0 - Modern System Information Monitor**
