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

## 🚀 Usage

### Run techofetch
```bash
techofetch
````

That’s it.
No arguments are required for normal use.

---

## ⚙️ Commands

### Install system-wide

Installs `techofetch` to `/usr/local/bin` so it can be run from anywhere.

```bash
sudo techofetch --install
```

---

### Update to the latest version

Downloads the latest release and shows how to replace the binary.

```bash
techofetch --update
```

---

### Show help

Displays available options.

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
