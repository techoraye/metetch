# 🖥️ techofetch

**A fast, animated system information tool for Linux terminals.**

`techofetch` displays detailed system information in a clean, colorful terminal interface with smooth live updates.  
It is designed to be simple to use, fast to start, and visually stable.

---

## 📸 What it does

`techofetch` shows:

- CPU model and live CPU load
- Memory usage (live)
- Disk usage
- OS and kernel information
- Installed package count
- Running processes and threads
- Shell, window manager / desktop environment
- Network information (local IP, public IP, VPN status)
- Battery status (if available)
- Weather (based on IP location)
- System uptime and current time (live)

All live values update **in place**, without flicker or overlapping text.

---

## 📦 Installation

### 🔹 Method 1: Install from GitHub Releases (recommended)

1. Go to:
```

[https://github.com/techoraye/techofetch/releases](https://github.com/techoraye/techofetch/releases)

````

2. Download the latest **`techofetch`** binary

3. Install it system-wide:
```bash
sudo install techofetch /usr/local/bin/techofetch
````

4. Run:

   ```bash
   techofetch
   ```

---

### 🔹 Method 2: Clone repository and build locally

> ⚠️ This method is intended for **personal/internal use only**.

```bash
git clone git@github.com:techoraye/techofetch.git
cd techofetch
```

Compile:

```bash
g++ techofetch.cpp -o techofetch \
  -std=gnu++17 \
  -O2 \
  -pthread \
  -lcurl
```

Install:

```bash
sudo install techofetch /usr/local/bin/techofetch
```

Run:

```bash
techofetch
```

---

## 🚀 Usage

### Run techofetch

```bash
techofetch
```

No arguments are required for normal use.

---

## ⚙️ Commands

### Install system-wide

Installs `techofetch` to `/usr/local/bin`.

```bash
sudo techofetch --install
```

---

### Update to the latest version

Checks GitHub Releases and downloads the latest binary.

```bash
techofetch --update
```

---

### Show help

```bash
techofetch --help
```

---

## ⌨️ Controls

* **Press `Enter`** to exit the program
* Live updates stop automatically when exiting

---

## 🐧 Requirements

* Linux system
* Terminal with ANSI color support
* Internet connection (optional, for weather and update checks)

---

## 🧾 Notes

* `techofetch` runs entirely in the terminal
* No configuration files are required
* If weather or public IP cannot be detected, those fields will show `N/A`
* Animation speed is optimized for fast startup
* Automatic update checks do **not** replace binaries without user action

---

## 📄 License

This software is **proprietary**.

You may use the software for personal or internal purposes, but you may **not**:

* modify it
* redistribute it
* publish it
* reverse engineer it

See the `LICENSE` file for full terms.

---

## ❤️ Author

Made with heart by **techoraye**
