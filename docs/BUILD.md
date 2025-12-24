# 🚀 Build Guide - Metetch v0.4

**Made with ❤️ • [GitHub](https://github.com/techoraye/metetch)**

## Information Display Structure

When you run `metetch`, it displays information organized as:

```
├─ System Information
│  ├─ Operating System
│  ├─ Kernel Version
│  ├─ Uptime
│  ├─ Current User
│  ├─ Shell & Terminal
│  └─ Desktop Environment
├─ Hardware
│  ├─ CPU Load & Temperature
│  ├─ Memory Usage
│  ├─ GPU Monitoring
│  ├─ Disk Usage
│  ├─ Audio System
│  ├─ Battery Status
│  └─ Display Resolution
├─ Network
│  ├─ Hostname
│  ├─ IP Address (IPv4/IPv6)
│  ├─ Network Interface
│  └─ VPN Status
├─ Security & Resources
│  ├─ CPU Frequency & Cores
│  ├─ Running Processes
│  ├─ Active Threads
│  └─ Package Manager
└─ Time & Weather
   ├─ Current Time
   ├─ Current Date
   └─ Weather Information
```

---

## ⚡ Automatic Installation (All Distros) - RECOMMENDED

The easiest way to build and install Metetch on any Linux distribution:

```bash
cd /path/to/metetch
sudo ./install.sh
```

The script will:
1. ✅ Auto-detect your Linux distribution
2. ✅ Install all required dependencies using your package manager
3. ✅ Build the project with optimizations
4. ✅ Install to `/usr/local/bin/metetch`
5. ✅ Create config directory
6. ✅ Generate checksums

**That's it!** Run: `metetch`

### Supported Distros
- ✅ Debian/Ubuntu (apt)
- ✅ Arch/Manjaro (pacman)
- ✅ Fedora/RHEL/CentOS (dnf/yum)
- ✅ openSUSE/SLES (zypper)
- ✅ Alpine Linux (apk)
- ✅ Void Linux (xbps)
- ✅ Gentoo (emerge)

---

## 📋 Verify Installation

After installation, verify the binary integrity:

```bash
./VERIFY.sh
```

This checks that all project files have not been modified.

---

## Manual Build (3 Commands)

If you prefer manual building without automatic dependency installation:

```bash
cd /path/to/metetch
make build
./build/metetch
```

Or using CMake directly:

```bash
cd /path/to/metetch
mkdir build && cd build
cmake .. && make -j$(nproc)
./metetch
```

---

## Step-by-Step Manual Build

### Step 1: Install Dependencies

Choose your operating system:

#### **Debian/Ubuntu**
```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake libcurl4-openssl-dev libncurses-dev libtinfo-dev pkg-config
```

#### **Arch/Manjaro**
```bash
sudo pacman -S base-devel cmake curl ncurses
```

#### **Fedora/RHEL/CentOS**
```bash
sudo dnf install -y gcc-c++ cmake libcurl-devel ncurses-devel libtinfo-devel pkg-config
```

#### **Alpine**
```bash
sudo apk add --no-cache build-base cmake curl-dev ncurses-dev linux-headers pkgconfig
```

#### **openSUSE/SLES**
```bash
sudo zypper install -y gcc-c++ cmake libcurl-devel ncurses-devel libtinfo-devel pkg-config
```

#### **Void Linux**
```bash
sudo xbps-install -Sy base-devel cmake curl-devel ncurses-devel pkgconfig
```

#### **Gentoo**
```bash
sudo emerge --sync
sudo emerge -qv dev-build/cmake net-misc/curl sys-libs/ncurses
```

---

### Step 2: Clone or Navigate to Project

```bash
# If cloning from git
git clone <repository-url>
cd metetch

# Or if you already have the code
cd /path/to/metetch
```

---

### Step 3: Build the Project

#### Option A: Using Makefile (Simplest)

```bash
make
```

**Output:** Binary will be in `./build/metetch`

---

#### Option B: Using CMake (Manual)

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build with make (uses all available cores)
make -j$(nproc)

# Or use specific number of cores
make -j4
```

**Output:** Binary will be in `./build/metetch`

---

### Step 4: Run the Application

```bash
# From project directory
./build/metetch

# Or copy to PATH
sudo cp build/metetch /usr/local/bin/metetch
metetch
```

---

## System-Wide Installation

### Using Install Script (Recommended)
```bash
sudo ./install.sh
```

### Manual Installation
```bash
# Build first
make build

# Install binary
sudo cp build/metetch /usr/local/bin/metetch
sudo chmod +x /usr/local/bin/metetch

# Create config directory
mkdir -p ~/.config/metetch

# Create default config
cat > ~/.config/metetch/config.ini << EOF
show_realtime_in_os=0
show_gpu=1
show_disk=1
theme=default
EOF
```

### Verify Installation
```bash
# Check binary exists
which metetch

# Run it
metetch

# Show help
metetch --help
```

---

## Uninstallation

### Using Metetch Uninstall
```bash
sudo metetch --uninstall
```

### Manual Uninstallation
```bash
# Remove binary
sudo rm /usr/local/bin/metetch

# Remove config (optional - preserves user settings)
rm -rf ~/.config/metetch
```

---

## Build Configuration Options

### CMake Flags

The project uses these compiler flags by default:

```cmake
-O3                      # Maximum optimization
-flto                    # Link-time optimization for smaller binary
-Wall -Wextra            # Strict warnings
-Wformat-security        # Security checks
-std=c++17               # C++17 standard
```

### Custom Build with Specific Flags

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O3 -flto" ..
make -j$(nproc)
```

### Build Types
- **Release** (Default): Optimized for performance
- **Debug**: With debug symbols for development
- **RelWithDebInfo**: Release with debug info

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
```

---

## Dependencies Explained

### Build-Time Dependencies
- **CMake** - Build system configuration
- **g++/clang++** - C++ compiler
- **make** - Build tool
- **pkg-config** - Library dependency checker

### Runtime Dependencies
- **libcurl** - HTTP requests (weather API, updates)
- **ncurses** - Terminal UI rendering
- **libtinfo** - Terminal information (ncurses dependency)

### Optional Dependencies
- **nvidia-smi** - For NVIDIA GPU monitoring
- **rocm-smi** - For AMD GPU monitoring
- **lspci** - For GPU device detection
- **lscpu** - For CPU information
- **lsb_release** - For OS detection

---

## Troubleshooting

### Issue: CMake not found
```bash
# Solution: Install cmake first
sudo apt-get install cmake          # Debian/Ubuntu
sudo pacman -S cmake                # Arch
sudo dnf install cmake              # Fedora
```

### Issue: Build fails with missing libraries
```bash
# Solution: Install development packages
# Debian/Ubuntu
sudo apt-get install libcurl4-openssl-dev libncurses-dev libtinfo-dev

# Arch
sudo pacman -S curl ncurses

# Fedora
sudo dnf install libcurl-devel ncurses-devel libtinfo-devel
```

### Issue: "pkg-config not found"
```bash
# Solution: Install pkg-config
sudo apt-get install pkg-config     # Debian/Ubuntu
sudo pacman -S pkg-config           # Arch
sudo dnf install pkg-config         # Fedora
```

### Issue: Binary not found after build
```bash
# Check build output
ls -la build/

# Rebuild from clean
make clean
make build

# Check for error messages in output
make build 2>&1 | tail -20
```

### Issue: "command not found: metetch" after install
```bash
# Check if binary was installed
which metetch
ls -la /usr/local/bin/metetch

# Reinstall if needed
sudo ./install.sh

# Or manual install
sudo cp build/metetch /usr/local/bin/metetch
sudo chmod +x /usr/local/bin/metetch

# Refresh shell
hash -r
```

### Issue: Terminal rendering issues
```bash
# Reset terminal
reset

# Try with different TERM setting
export TERM=xterm-256color
metetch

# Try different terminal emulator
# Works best in: gnome-terminal, konsole, xterm, alacritty, kitty
```

---

## Performance Notes

- **Compilation**: ~5-10 seconds on modern hardware
- **Binary Size**: ~130-150 KB (stripped)
- **First Run**: <500ms startup time
- **Memory Usage**: ~15-25 MB during operation
- **CPU Usage**: <1% idle, <5% during updates

---

## Next Steps

After successful build and installation:

1. **Run Metetch**
   ```bash
   metetch
   ```

2. **Configure Settings** (Optional)
   ```bash
   metetch --config
   ```

3. **Check for Updates** (Optional)
   ```bash
   metetch --update
   ```

4. **Read Documentation**
   - [QUICKSTART.md](QUICKSTART.md) - 2-minute quick start
   - [DESIGN.md](DESIGN.md) - Design philosophy
   - [COLOR_PALETTE.md](COLOR_PALETTE.md) - Visual reference
   - [DOCUMENTATION_INDEX.md](DOCUMENTATION_INDEX.md) - Full docs index

---

**Happy monitoring! ⚡**

For issues or questions, please refer to the [DOCUMENTATION_INDEX.md](DOCUMENTATION_INDEX.md).
