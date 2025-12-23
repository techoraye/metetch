# Metetch Developer Documentation Index

## 📚 Documentation Structure

### For Version Management
📄 **[VERSION_GUIDE.md](VERSION_GUIDE.md)** - Quick reference for changing version
- **Where**: `src/utils.cpp` line 20
- **Format**: `const string ver = "2.0.0";`
- **Quick change**: Just edit that one line and rebuild

### For Getting Started
📄 **[DEV_QUICKSTART.md](DEV_QUICKSTART.md)** - 15-minute quick start guide
- Build instructions
- Understanding the codebase
- Common commands
- First contribution steps
- **Best for**: New developers

### For Complete Reference
📄 **[DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md)** - Complete developer documentation
- Architecture overview
- Code structure
- Module system
- Data flow
- Adding new features
- Testing & debugging
- Performance considerations
- **Best for**: Deep dives and reference

### Features & Changes
📄 **[FEATURES_NEW.md](FEATURES_NEW.md)** - New features in v2.0.0
- GPU usage monitoring ⚡
- Advanced CPU metrics 🔥
- Extended network info 🌐
- Security monitoring 🔐
- Resource tracking 💾
- **Best for**: Understanding what's new

---

## 🎯 Most Common Tasks

### Change Version
**File**: [src/utils.cpp](../src/utils.cpp) line 20
```cpp
const string ver = "0.3";  ← Change to your version
```
Then: `cd build && make clean && make`

**Guide**: [VERSION_GUIDE.md](VERSION_GUIDE.md)

### Add New Feature
1. Create module header in `include/modules/`
2. Implement in `src/modules/`
3. Add fields to `include/data_types.h`
4. Collect in `src/collect.cpp`
5. Display in `src/render.cpp`

**Guide**: [DEV_QUICKSTART.md](DEV_QUICKSTART.md) section 5 or [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md)

### Understand Architecture
**Guide**: [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md) - Architecture section
```
main() → collect() → render() → Display
            ↓
        (all modules)
```

### Build Project
```bash
cd build
cmake ..
make -j$(nproc)
./metetch
```

**Guide**: [DEV_QUICKSTART.md](DEV_QUICKSTART.md) section 1

---

## 📖 Reading Order

### If you have 5 minutes
→ Read: [VERSION_GUIDE.md](VERSION_GUIDE.md)

### If you have 15 minutes
→ Read: [DEV_QUICKSTART.md](DEV_QUICKSTART.md)

### If you have 1 hour
→ Read: [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md)

### If you want feature details
→ Read: [FEATURES_NEW.md](FEATURES_NEW.md)

---

## 🔧 Quick Reference

### File Locations

| What | File | Line |
|------|------|------|
| **VERSION** | `src/utils.cpp` | 20 |
| **Main entry** | `src/main.cpp` | - |
| **Data collection** | `src/collect.cpp` | - |
| **Display** | `src/render.cpp` | - |
| **GPU module** | `src/modules/hardware/gpu.cpp` | - |
| **Data structures** | `include/data_types.h` | - |
| **Build config** | `CMakeLists.txt` | - |

### Build Commands

```bash
# In the build/ directory
cmake ..                    # Configure
make -j$(nproc)            # Build
make clean                 # Clean
./metetch                  # Run
```

### Module Structure

```
src/modules/
├── hardware/          ← CPU, GPU, memory, temp, disk
├── network/           ← Network, IP, gateway, DNS
└── system/            ← OS, kernel, users, security
```

---

## 🆕 What's New (v2.0.0)

### GPU Monitoring ⚡
- Real-time GPU usage %
- GPU temperature 
- GPU memory usage
- Power draw (W)
- Support for NVIDIA, AMD, Intel

### CPU Metrics 🔥
- Real-time frequency
- Core/thread count
- TDP and power draw
- Thermal status

### Network Info 🌐
- IPv4 & IPv6
- Gateway & DNS
- MAC address
- Bytes sent/received
- Latency & packet loss

### System Features 🔐💾
- Security (SELinux, AppArmor, firewall)
- Failed login attempts
- Disk usage details
- I/O statistics

---

## 📋 Developer Checklist

- [ ] Read [DEV_QUICKSTART.md](DEV_QUICKSTART.md)
- [ ] Build the project
- [ ] Change version to test
- [ ] Run `./metetch`
- [ ] Study `src/main.cpp`
- [ ] Look at a module (e.g., `src/modules/hardware/gpu.cpp`)
- [ ] Read [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md)
- [ ] Plan your feature
- [ ] Code it following patterns
- [ ] Test build: `make && ./metetch`
- [ ] Commit with meaningful message

---

## 🚀 Next Steps

1. **Setup** → Read [DEV_QUICKSTART.md](DEV_QUICKSTART.md)
2. **Build** → `mkdir build && cd build && cmake .. && make`
3. **Version** → Edit `src/utils.cpp` line 20
4. **Code** → Follow module patterns
5. **Reference** → Use [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md)

---

## 📝 Documentation Files in This Directory

```
docs/
├── README.md                    ← User overview
├── QUICKSTART.md               ← User quick start
├── BUILD.md                    ← Build instructions
├── COLOR_PALETTE.md            ← Color scheme
├── DESIGN.md                   ← Design philosophy
├── DOCUMENTATION_INDEX.md      ← Full index
│
├── FEATURES_NEW.md             ← New v2.0 features
├── DEVELOPER_GUIDE.md          ← Complete dev reference ⭐
├── DEV_QUICKSTART.md           ← 15-min quick start ⭐
├── VERSION_GUIDE.md            ← Version management ⭐
└── DEVELOPER_INDEX.md          ← This file
```

⭐ = New developer documentation

---

## 💡 Tips for Success

1. **Start simple** - Change version first to learn the build process
2. **Follow patterns** - Copy code style from existing modules
3. **Test often** - Build after each change
4. **Ask questions** - Check comments in similar code
5. **Document well** - Add comments to your code
6. **Read carefully** - This doc has all answers

---

## 🐛 Common Issues & Solutions

| Issue | Solution | Reference |
|-------|----------|-----------|
| Can't find version | Line 20 of `src/utils.cpp` | [VERSION_GUIDE.md](VERSION_GUIDE.md) |
| Build fails | Install dependencies, check cmake | [DEV_QUICKSTART.md](DEV_QUICKSTART.md) |
| Don't understand structure | Read architecture section | [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md) |
| Want to add feature | Follow 5-step pattern | [DEV_QUICKSTART.md](DEV_QUICKSTART.md) |
| Need full reference | Read complete guide | [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md) |

---

## 📞 Support

- **Quick questions**: Check [DEV_QUICKSTART.md](DEV_QUICKSTART.md)
- **Architecture questions**: See [DEVELOPER_GUIDE.md](DEVELOPER_GUIDE.md)
- **Version questions**: Read [VERSION_GUIDE.md](VERSION_GUIDE.md)
- **Feature details**: Check [FEATURES_NEW.md](FEATURES_NEW.md)
- **Code patterns**: Study existing modules in `src/modules/`

---

**Start with [DEV_QUICKSTART.md](DEV_QUICKSTART.md) if you're new! 🚀**

---

**Last Updated**: December 2024
**Documentation Status**: Complete
**For Metetch Version**: 2.0.0+
