# Metetch Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.5.0] - 2025-12-22

### ✨ Major Features & Improvements

#### Made with ❤️ - Brand & Attribution Updates
- **Heart Branding**: Added "Made with ❤️" to footer of all displays
- **GitHub Link**: Modern GitHub link display in all user-facing output
- **Professional Attribution**: Clear GitHub URL in messages: https://github.com/techoraye/metetch

#### Minimal/Compact Display Mode (NEW)
- **New `--minimum` flag**: Display essential system info in compact format
- **Short form `-m`**: Quick alias for the flag
- **Compact layout**: All info on minimal lines without verbose output
- **Perfect for scripting**: Easy to parse essential information
- **Includes**: OS, kernel, uptime, user, CPU, memory, disk, hostname, IP, optional GPU
- **New Files**:
  - `include/minimal.h` - Header for minimal display functionality
  - `src/minimal.cpp` - Implementation of compact display mode

#### Updated Updater System
- **Non-Real-Time Mode**: Application no longer stays open after displaying update information
- **Auto-Exit**: System automatically exits after showing update message (3 second delay)
- **Improved Update Display**: Cleaner update notification popup with modern formatting
- **GitHub Integration**: Update messages now include modern GitHub repository link
- **Quick Installation**: Streamlined update installation flow with immediate feedback

#### Documentation Overhaul
- **Tree Structure Display**: All documentation updated with modern tree-style information hierarchy
- **README.md**: Added comprehensive information display structure with ASCII tree
- **BUILD.md**: Includes detailed tree structure of what information is displayed
- **QUICKSTART.md**: Updated with information hierarchy visualization
- **DOCUMENTATION_INDEX.md**: Enhanced with display structure and GitHub attribution
- **DESIGN.md**: Design philosophy now includes "Made with ❤️" and information hierarchy

#### Information Display Structure
New standardized tree format for displaying all system information:
```
├─ System Information
├─ Hardware Status
├─ Network Information
├─ Security & Resources
└─ Date, Time & Weather
```

### 🔧 Code Changes

#### Render System (`src/render.cpp`)
- Updated footer with "Made with ❤️" message
- Modern GitHub URL display with icon
- Improved color formatting for footer information
- Professional attribution styling

#### Update Handler (`src/update.cpp`)
- Enhanced update notification popup
- Added "Made with ❤️" to update messages
- Included GitHub repository link in update messages
- Improved message formatting and visual hierarchy

#### Main Application (`src/main.cpp`)
- Fixed updater thread behavior for non-real-time display
- Auto-exit after update notification (3-second display window)
- Reduced initial check delay from 5 to 2 seconds
- Proper cleanup on update detection
- Added `#include "minimal.h"` for minimal display
- New `--minimum` / `-m` flag handler
- Routes to `renderMinimalDisplay()` for compact output
- Updated help text with new flag options
- Fixed missing closing brace (syntax error)

#### Minimal Display (`src/minimal.cpp`) - NEW FILE
- New implementation of compact system information display
- Shows essential info in single-line format for each category
- Includes OS, kernel, uptime, user, CPU, memory, disk, hostname, IP
- Optional GPU display if available
- Professional footer with "Made with ❤️" and GitHub link
- Color-coded using existing color palette

#### Minimal Header (`include/minimal.h`) - NEW FILE
- Function declaration for `renderMinimalDisplay()`
- Documentation for minimal display mode
- Clean interface for compact information rendering

#### Build System (`CMakeLists.txt`)
- Added `src/minimal.cpp` to SOURCES list
- Properly integrated new minimal display compilation

### 📚 Documentation Changes

#### README.md
- Added GitHub link at top: https://github.com/techoraye/metetch
- Added "Made with ❤️" branding statement
- New "Information Display" section with tree structure
- Updated feature descriptions with modern formatting

#### BUILD.md
- Added "Made with ❤️" attribution
- Added GitHub link
- New "Information Display Structure" section with tree format
- All information types documented with hierarchy

#### QUICKSTART.md
- Added GitHub link and heart branding at top
- New "Information Structure" section with ASCII tree
- New "Try the Minimal Mode" section showing `--minimum` usage
- Clear hierarchy showing what metetch displays
- Updated quick start instructions

#### DOCUMENTATION_INDEX.md
- Added "Made with ❤️" at top
- New "Information Structure" section
- Comprehensive tree display of what's shown
- Updated navigation with GitHub link

#### DESIGN.md
- Added GitHub attribution and heart branding
- New "Information Display Structure" section
- Complete tree showing design hierarchy
- Updated design philosophy with heart branding mention

### 🐛 Bug Fixes & Improvements

- Fixed updater exit behavior (no longer hangs)
- Improved update message timing and display
- Better cleanup of update threads
- More responsive application shutdown

### ⚙️ Technical Details

- C++17 standard maintained
- CMake build system unchanged
- All dependencies compatible
- Performance optimizations maintained (-O3 -flto)

### 📊 Version Information

- **Previous Version:** 0.4.0
- **Current Version:** 0.5.0
- **Build Date:** December 22, 2025
- **Repository:** https://github.com/techoraye/metetch

---

## [0.4.0] - 2025-12-22

See previous release notes for v0.4.0 features.
