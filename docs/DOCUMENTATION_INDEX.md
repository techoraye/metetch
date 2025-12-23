# 📖 Metetch Documentation Index

## 🚀 Getting Started (Choose Your Path)

### ⚡ In a Hurry? (2 minutes)
👉 **[QUICKSTART.md](docs/QUICKSTART.md)** - 3 commands and you're done

### 📚 Want Full Details? (10 minutes)
👉 **[BUILD.md](docs/BUILD.md)** - Comprehensive build guide with troubleshooting

### 🎨 Curious About Design? (15 minutes)
👉 **[DESIGN.md](docs/DESIGN.md)** - Design philosophy & decisions

### 🎭 Want to See Colors? (5 minutes)
👉 **[COLOR_PALETTE.md](docs/COLOR_PALETTE.md)** - Visual color reference

### 📋 Everything About Features? (20 minutes)
👉 **[README.md](docs/README.md)** - Full feature documentation

---

## 📍 Quick Navigation

### For Different User Types

| You are... | Start here |
|-----------|-----------|
| **New to Linux/Building** | [QUICKSTART.md](docs/QUICKSTART.md) |
| **Developer** | [BUILD.md](docs/BUILD.md) |
| **Designer/Visual** | [COLOR_PALETTE.md](docs/COLOR_PALETTE.md) |
| **Want full info** | [README.md](docs/README.md) |
| **Curious about design** | [DESIGN.md](docs/DESIGN.md) |

---

## 🎯 The 30-Second Overview

**Metetch** is a beautiful, system information tool for Linux.

### What It Does
Shows you:
- CPU, Memory, Disk usage
- Network information
- System uptime and date
- GPU info (if available)
- And much more!

### What Makes It Special
- 🎨 Modern, minimal design (NOT retro)
- ⚡ Super fast (written in C++)
- 💻 Lightweight (minimal resources)
- 🎯 Easy to use (just run it!)
- 📸 Beautiful screenshots

### Quick Build
```bash
cd metetch
make
./build/metetch
```

---

## 📂 Documentation Files

### Quick Reference

| File | Size | Focus | Time |
|------|------|-------|------|
| **QUICKSTART.md** | 2 KB | Start here fast | 2 min |
| **BUILD.md** | 8 KB | How to build | 10 min |
| **README.md** | 14 KB | All features | 20 min |

### Design Documentation

| File | Size | Focus | Time |
|------|------|-------|------|
| **DESIGN.md** | 16 KB | Design philosophy | 15 min |
| **COLOR_PALETTE.md** | 12 KB | Colors & visuals | 10 min |

---

## 🚀 Build Paths

### Path 1: The Quick Path (Ubuntu/Debian)
```bash
sudo apt-get install build-essential cmake libcurl4-openssl-dev libncurses-dev
cd metetch
make
./build/metetch
```

### Path 2: The Detailed Path
1. Read [QUICKSTART.md](QUICKSTART.md)
2. Install dependencies for your OS
3. Run the build commands
4. Enjoy!

### Path 3: The Full Understanding Path
1. Start with [README.md](docs/README.md) for overview
2. Read [BUILD.md](docs/BUILD.md) for build details
3. Check [DESIGN.md](docs/DESIGN.md) for design
4. Look at [COLOR_PALETTE.md](docs/COLOR_PALETTE.md) for visuals
5. Build and run

---

## ✨ Key Features (30-Second Summary)

### Display Capabilities
- ✓ System information (OS, kernel, uptime)
- ✓ Hardware metrics (CPU, memory, disk, GPU)
- ✓ Network information (IP, interface, VPN)
- ✓ Real-time updates
- ✓ Temperature monitoring
- ✓ Process/thread counting

### User Experience
- ✓ Beautiful UI
- ✓ No configuration needed (works out of box)
- ✓ Optional config menu
- ✓ Real-time data updates
- ✓ Fast, lightweight
- ✓ Works on any Linux distro

### Customization
- ✓ Configuration menu: `metetch --config`
- ✓ Show/hide GPU info
- ✓ Show/hide disk info
- ✓ Theme options
- ✓ Settings saved locally

---

## 🎨 Design Highlights

### Visual Design
```
✓ Geometric logo (not chunky ASCII)
✓ Thin borders (minimal, modern)
✓ Strategic colors (cyan, purple, lime)
✓ Flat progress bars (▸▹ style)
✓ Professional layout
✓ KDE Plasma / Wayland inspired
✓ Dark terminal optimized
✓ Screenshot ready
```

---

## 💻 Installation Methods

### Method 1: System-Wide (Recommended)
```bash
cd metetch
make
cd build
sudo make install
# Now use: metetch (from anywhere)
```

### Method 2: Local Binary
```bash
cd metetch
make
./build/metetch
```

### Method 3: From Source
```bash
mkdir build && cd build
cmake ..
make
./metetch
```

---

## 🐛 Quick Troubleshooting

| Problem | Solution | Reference |
|---------|----------|-----------|
| Build fails | Install dependencies | [BUILD.md](docs/BUILD.md) |
| Can't find cmake | Install build tools | [BUILD.md](docs/BUILD.md) |
| Linker errors | Clean build | [BUILD.md](docs/BUILD.md) |
| Permission denied | Run chmod +x | [BUILD.md](docs/BUILD.md) |
| Need help | Read BUILD.md | [BUILD.md](docs/BUILD.md) |

---

## ⏱️ Time Estimates

| Task | Time | File |
|------|------|------|
| Quick start | 2 min | QUICKSTART.md |
| Build from source | 5 min | BUILD.md |
| Understand design | 15 min | DESIGN.md |
| Install system-wide | 10 min | BUILD.md |
| Learn all features | 20 min | README.md |
| Full deep dive | 1 hour | All files |

---

## 🎁 What You Get

### When You Clone This Repo
- ✓ C++ source code
- ✓ Beautiful system information tool
- ✓ Comprehensive documentation
- ✓ Easy build system
- ✓ Configuration options
- ✓ Real-time updates

### When You Build It
- ✓ Fast binary (~200KB)
- ✓ No runtime dependencies*
- ✓ System integration ready
- ✓ Full functionality

### When You Run It
- ✓ Beautiful display
- ✓ Live system information
- ✓ Professional appearance
- ✓ Real-time updates

---

## 📞 Quick Links

| What | Link |
|------|------|
| **Quick Start** | [QUICKSTART.md](docs/QUICKSTART.md) |
| **Build Guide** | [BUILD.md](docs/BUILD.md) |
| **Full Docs** | [README.md](docs/README.md) |
| **Design Docs** | [DESIGN.md](docs/DESIGN.md) |
| **Colors** | [COLOR_PALETTE.md](docs/COLOR_PALETTE.md) |

---

## 🚀 Next Steps

1. **Choose your path** above
2. **Read the appropriate guide** (usually QUICKSTART.md)
3. **Install dependencies** for your OS
4. **Build the project** (usually just `make`)
5. **Run metetch** (`./build/metetch`)
6. **Enjoy!** ✨

---

**Welcome to Metetch!** 🎉

Choose a guide above and you'll be up and running in minutes.
