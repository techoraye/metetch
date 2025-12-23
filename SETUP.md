# 🔒 METETCH - Secure Installation Guide

**metetch** is proprietary software under the **METETCH PROPRIETARY LICENSE**. This guide ensures secure and authorized installation.

## 📋 Prerequisites

Your system must have:
- Linux kernel 4.0+
- glibc 2.27+
- libcurl 7.50+
- ncurses 6.0+
- C++17 compiler (for building)

## 🔐 Verification Before Installation

Always verify file integrity before installation:

```bash
./VERIFY.sh
```

This confirms that:
- ✅ All files are authentic and unmodified
- ✅ No tampering has occurred
- ✅ Checksums match expected values

## 🚀 Installation Steps

### Step 1: Install Dependencies

**Debian/Ubuntu:**
```bash
sudo apt-get install build-essential cmake libcurl4-openssl-dev libncurses-dev libtinfo-dev
```

**Arch/Manjaro:**
```bash
sudo pacman -S base-devel cmake curl ncurses
```

**Fedora/RHEL:**
```bash
sudo dnf install gcc-c++ cmake libcurl-devel ncurses-devel libtinfo-devel
```

### Step 2: Run Installation Script

```bash
chmod +x install.sh
sudo ./install.sh
```

The script will:
- ✅ Check all dependencies
- ✅ Build metetch from source
- ✅ Install to `/usr/local/bin` (requires sudo)
- ✅ Create configuration directory

### Step 3: Verify Installation

```bash
metetch --help
```

If the command is not found, use the full path:
```bash
/usr/local/bin/metetch
```

## 💻 Using metetch

### Display System Information
```bash
metetch
```

### Open Configuration Menu
```bash
metetch --config
```

### Check for Updates
```bash
metetch --update
```

### Get Help
```bash
metetch --help
```

## 🔐 License Compliance

This software is **proprietary and confidential**. By using metetch, you agree to:

✅ **Permitted:**
- Using the software for personal or internal purposes
- Viewing the source code (when provided)

❌ **Prohibited:**
- Modifying the source code
- Publishing or distributing the software
- Creating derivative works
- Reverse engineering or decompiling
- Commercial use without permission

For licensing inquiries or commercial use, contact the author directly.

## 📦 Uninstallation

To remove metetch from your system:

```bash
sudo rm /usr/local/bin/metetch
rm -rf ~/.config/metetch
```

## 🆘 Troubleshooting

### Command Not Found
- Ensure installation completed successfully
- Check that `/usr/local/bin` is in your PATH: `echo $PATH`
- Try the full path: `/usr/local/bin/metetch`

### Installation Fails
- Run the verification script: `./VERIFY.sh`
- Ensure all dependencies are installed
- Check that you have write permissions to `/usr/local/bin`
- Try installing with explicit sudo: `sudo ./install.sh`

### Missing Features
- Open the configuration menu: `metetch --config`
- Verify that required system tools are available
- Check `/var/log/metetch` for error logs (if available)

## 📞 Support

For issues or inquiries, contact the author directly.

---

**Copyright © 2025 techoraye**  
**Licensed under METETCH PROPRIETARY LICENSE**  
All rights reserved.
