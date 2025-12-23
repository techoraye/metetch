# 🚀 Metetch v0.4 - Quick Start Guide

**Made with ❤️ • [GitHub](https://github.com/techoraye/metetch)**

## ⚡ Super Quick Build & Install (All Distros)

```bash
cd metetch
sudo ./install.sh
```

**Done!** The script auto-detects your distro, installs dependencies, builds, and installs the binary.

Run: `metetch`

### What the installer does:
- ✅ Detects Debian, Ubuntu, Arch, Fedora, openSUSE, Alpine, Void, Gentoo, etc.
- ✅ Installs build tools, cmake, libcurl-dev, libncurses-dev
- ✅ Builds the project
- ✅ Installs to `/usr/local/bin/metetch`
- ✅ Creates config in `~/.config/metetch/`

---

## Information Structure

```
metetch displays:

├─ System Information
│  ├─ OS & Kernel Version
│  ├─ System Uptime
│  ├─ Current User
│  ├─ Shell & Terminal
│  └─ Desktop Environment
├─ Hardware Status
│  ├─ CPU Load & Temperature
│  ├─ Memory Usage & Free
│  ├─ GPU Info (if available)
│  ├─ Disk Usage (all partitions)
│  ├─ Battery Status
│  └─ Display Resolution
├─ Network
│  ├─ Hostname
│  ├─ IP Address
│  └─ Interface Info
└─ Date & Time
   ├─ Current Time
   ├─ Current Date
   └─ Weather (if available)
```

---

## 🔧 Local Testing (Without System Install)

```bash
cd metetch
make
./build/metetch
```

No `sudo` needed - binary runs from current directory.

### Try the Minimal Mode

```bash
./build/metetch --minimum
# or
./build/metetch -m
```

Shows compact information on fewer lines - great for quick checks!

---

## 📋 Manual Build (If install.sh doesn't work)

### Step 1: Install Dependencies

**Choose your distro:**

<details>
<summary><b>Ubuntu/Debian</b></summary>

```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake libcurl4-openssl-dev libncurses-dev libtinfo-dev pkg-config
```
</details>

<details>
<summary><b>Arch/Manjaro</b></summary>

```bash
sudo pacman -S base-devel cmake curl ncurses
```
</details>

<details>
<summary><b>Fedora/RHEL</b></summary>

```bash
sudo dnf install -y gcc-c++ cmake libcurl-devel ncurses-devel libtinfo-devel pkg-config
```
</details>

<details>
<summary><b>Alpine</b></summary>

```bash
sudo apk add --no-cache build-base cmake curl-dev ncurses-dev linux-headers pkgconfig
```
</details>

---

### Step 2: Build It

```bash
cd metetch
mkdir build
cd build
cmake ..
make
```

---

### Step 3: Run It

```bash
./metetch
```

**Enjoy the modern, beautiful system info display!** ✨

---

## 🎯 What if Something Goes Wrong?

### "command not found: cmake"
```bash
# Install CMake
sudo apt-get install cmake  # Ubuntu/Debian
sudo pacman -S cmake        # Arch
sudo dnf install cmake      # Fedora
```

### "command not found: g++"
```bash
# Install compiler
sudo apt-get install build-essential  # Ubuntu/Debian
sudo pacman -S base-devel             # Arch
sudo dnf install gcc-c++              # Fedora
```

### Build fails with library errors
```bash
# Clean and rebuild
cd metetch
rm -rf build
mkdir build
cd build
cmake ..
make
```

---

## 📦 Install System-Wide (Optional)

Want to use `metetch` from anywhere?

```bash
cd metetch/build
sudo make install
metetch  # Now works from anywhere!
```

---

## 🎨 What Makes This Special?

✨ **Modern Design**
- Clean, geometric logo (not blocky)
- Thin, minimal borders
- Professional color scheme
- KDE Plasma / Wayland inspired

⚡ **Fast & Lightweight**
- Written in C++
- Real-time updates
- No performance impact

🎯 **Easy to Use**
- Just run it
- Beautiful output
- No configuration needed

---

## 🔧 Useful Commands

```bash
# Display system info
./build/metetch

# Show help
./build/metetch --help

# Open configuration menu
./build/metetch --config

# Check for updates
./build/metetch --update

# Install updates
./build/metetch --install
```

---

## 📚 More Information

- **Full build guide**: [BUILD.md](BUILD.md)
- **Design details**: [DESIGN.md](DESIGN.md)
- **Color reference**: [COLOR_PALETTE.md](COLOR_PALETTE.md)
- **Main docs**: [README.md](README.md)

---

## ✅ Success! You've Got Metetch

Once you see the beautiful system information display with:
- Modern geometric logo
- Clean bordered sections
- Cyan/purple/lime color accents
- Professional layout

**You're all set!** 🎉

---

**Questions?** Check [BUILD.md](BUILD.md) for detailed troubleshooting.

