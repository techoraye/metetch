# Release Notes - Metetch v0.5.0

## 🎉 Quality of Life Update: Modern UX & Documentation

**Release Date:** December 22, 2025  
**Version:** 0.5.0  
**Status:** Stable ✅

**Made with ❤️ • [GitHub Repository](https://github.com/techoraye/metetch)**

---

## 🌟 What's New in v0.5.0

### ❤️ Made with Heart - Brand Update
Show your love for the project! Metetch now proudly displays:
- **"Made with ❤️"** in all application footers
- **Modern GitHub link** for easy access: https://github.com/techoraye/metetch
- Clean, professional attribution throughout the application

### 🎯 NEW: Minimal/Compact Display Mode
Perfect for users who want less text or need to integrate with scripts:

```bash
metetch --minimum
# or
metetch -m
```

**What it shows:**
```
⚡ Metetch System Info
──────────────────────────────────────
OS: Ubuntu  |  Kernel: 6.1.0
Uptime: 2 days 3 hours  |  User: techoraye
CPU: 45.2%  |  MEM: 8192/16384MB  |  Disk: 245GB used / 500GB total
Hostname: mypc  |  IP: 192.168.1.100
GPU: NVIDIA RTX 4090
──────────────────────────────────────
⚡ Made with ❤️  by Techoraye
🔗 GitHub: https://github.com/techoraye/metetch
```

**Features:**
- ✅ Single-line format for each category
- ✅ Essential information only (OS, kernel, uptime, user, CPU, memory, disk, hostname, IP)
- ✅ Optional GPU display
- ✅ Same color-coded styling
- ✅ Perfect for quick checks or embedding in scripts

**New Files:**
- `include/minimal.h` - Minimal display interface
- `src/minimal.cpp` - Compact information rendering implementation

### 🔄 Fixed Update System
The updater now works smoothly:
- **Non-blocking Display**: Shows update message and exits automatically
- **Quick Notification**: Checks for updates every 2 seconds
- **3-Second Display Window**: Update message stays visible for 3 seconds before exiting
- **No More Hangs**: Application doesn't stay open waiting for real-time updates
- **Modern GitHub Integration**: Update messages include GitHub repository link

### 📚 Completely Revamped Documentation
All docs now feature modern tree-based information hierarchy:
- **README.md**: Information display structure with ASCII tree format
- **BUILD.md**: Complete guide with information hierarchy visualization
- **QUICKSTART.md**: Quick reference showing what metetch displays
- **DOCUMENTATION_INDEX.md**: Enhanced navigation with display structure
- **DESIGN.md**: Design philosophy includes heart branding

#### Example Information Structure
```
metetch displays information organized as:

├─ System Information
│  ├─ Operating System
│  ├─ Kernel Version
│  ├─ Uptime
│  └─ Current User
├─ Hardware Status
│  ├─ CPU Load & Temperature
│  ├─ Memory Usage
│  ├─ GPU Monitoring
│  └─ Disk Usage
├─ Network Information
│  ├─ Hostname
│  ├─ IP Address
│  └─ Network Interface
├─ Security & Resources
│  ├─ CPU Frequency & Cores
│  └─ Running Processes
└─ Date, Time & Weather
   ├─ Current Time
   └─ Weather Information
```

---

## ✨ Improvements Summary

### User Experience
- ✅ Application no longer hangs after showing updates
- ✅ Cleaner update notifications with modern formatting
- ✅ "Made with ❤️" branding shows passion for the project
- ✅ Easy GitHub access from everywhere in the app
- ✅ Professional footer design
- ✅ NEW: Minimal mode for quick information display
- ✅ NEW: Short `-m` flag for easy minimal access

### Documentation
- ✅ Modern tree-style information display format
- ✅ All documentation files updated consistently
- ✅ Clear hierarchy of what information is displayed
- ✅ GitHub repository link on every documentation file
- ✅ Better visual organization with ASCII trees

### Code Quality
- ✅ Fixed updater thread cleanup
- ✅ Improved timing and responsiveness
- ✅ Better separation of concerns in update logic
- ✅ Cleaner error handling

---

## 🚀 Quick Start

### Install (Automatic - All Distros)
```bash
git clone https://github.com/techoraye/metetch.git
cd metetch
sudo ./install.sh
```

### Run
```bash
metetch
```

### Check Updates
```bash
metetch --update
```

---

## 📊 What's Displayed

When you run `metetch`, you see:

```
├─ System Information
│  ├─ Operating System
│  ├─ Kernel Version
│  ├─ Uptime
│  ├─ Current User
│  ├─ Shell & Terminal
│  └─ Desktop Environment
├─ Hardware Monitoring
│  ├─ CPU Load & Temperature
│  ├─ Memory Usage
│  ├─ GPU Monitoring (optional)
│  ├─ Disk Usage
│  ├─ Audio System
│  ├─ Battery Status
│  └─ Display Resolution
├─ Network Information
│  ├─ Hostname
│  ├─ IP Address (IPv4/IPv6)
│  ├─ Network Interface
│  └─ VPN Status
├─ Security & Resources
│  ├─ CPU Frequency & Cores
│  ├─ Running Processes
│  ├─ Active Threads
│  └─ Package Manager
└─ Date, Time & Weather
   ├─ Current Time
   ├─ Current Date
   └─ Weather Information
```

---

## 🔗 Repository

**GitHub:** [https://github.com/techoraye/metetch](https://github.com/techoraye/metetch)

Made with ❤️ by Techoraye

---

## 📋 Upgrading from v0.4.0

To upgrade to v0.5.0:

```bash
cd /path/to/metetch
git pull origin main
sudo ./install.sh
```

Or check for updates:
```bash
metetch --update
metetch --install
```

---

## 🐛 Fixed Issues

- ✅ Updater no longer causes application to hang
- ✅ Update messages display correctly before exit
- ✅ Proper thread cleanup on update detection
- ✅ GitHub link now consistently displayed

---

## 📚 Documentation

All documentation has been updated with:
- Modern tree-style formatting
- "Made with ❤️" attribution
- GitHub repository links
- Clear information hierarchy
- Better visual organization

Check out:
- [README.md](https://github.com/techoraye/metetch) - Full feature documentation
- [BUILD.md](https://github.com/techoraye/metetch/blob/main/docs/BUILD.md) - Build guide
- [QUICKSTART.md](https://github.com/techoraye/metetch/blob/main/docs/QUICKSTART.md) - 2-minute quick start

---

## 🙏 Thank You

Made with ❤️ for the Linux community!

**Version:** 0.5.0  
**Release Date:** December 22, 2025  
**GitHub:** https://github.com/techoraye/metetch
