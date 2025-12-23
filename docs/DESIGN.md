# Metetch Design - Complete Refactor

**Made with ❤️ • [GitHub](https://github.com/techoraye/metetch)**

## Information Display Structure

```
metetch displays system information in this hierarchy:

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

## Overview

Metetch v0.4 deliver a **minimal, professional, KDE Plasma/Wayland-inspired terminal UI**. The new design prioritizes clarity, hierarchy, and aesthetic elegance while maintaining peak performance.

---

## 🎨 Design Philosophy

### Core Principles

1. **Minimal, Not Retro** - Clean borders, no excessive ASCII noise
2. **Thin Strokes** - geometric design, not chunky blocks
3. **Professional Hierarchy** - Clear visual structure with strategic emphasis
4. **Dark Terminal Optimized** - Designed for dark background terminals
5. **Screenshot Ready** - Every element carefully crafted for presentation
6. **Accessible Colors** - High contrast, no color-blind conflicts

---

**Design Features:**
- Thin geometric strokes (no thick blocks)
- Layered/outlined appearance
- Digital blueprint aesthetic
- Symmetrical frame with corner accents (◇)
- "metetch" branding integrated directly
- Made with ❤️
- Scalable and readable

---

## 🎨 Color Palette

### Primary Accent Colors

| Name | Code | Purpose | RGB |
|------|------|---------|-----|
| **Cyan** | `ACCENT_CYAN` | UI borders, primary highlights | #00ffff (51) |
| **Purple** | `ACCENT_PURPLE` | Secondary accent, memory stats | #d787ff (177) |
| **Lime** | `ACCENT_LIME` | Success states, good indicators | #87ff00 (118) |

### Text Colors

| Name | Code | Purpose | RGB |
|------|------|---------|-----|
| **TEXT_BRIGHT** | Main text, values | #ffffff (231) |
| **TEXT_LABEL** | Section labels | #dadada (251) |
| **TEXT_MUTED** | Secondary text | #808080 (244) |
| **TEXT_DIM** | Very subtle elements | #3a3a3a (238) |

### Status Colors

| Name | Code | Purpose | RGB |
|------|------|---------|-----|
| **STATUS_OK** | Green indicators, good states | #87d787 (113) |
| **STATUS_WARN** | Orange warnings, cautions | #ffaf00 (208) |
| **STATUS_CRIT** | Red alerts, critical temps | #ff0000 (196) |
| **STATUS_INFO** | Blue informational | #0087ff (39) |

---

## 📐 Layout & Structure

### Border System

**Thin Line Characters:**
- Top-left: `┌` (lighter than `╔`)
- Top-right: `┐`
- Bottom-left: `└`
- Bottom-right: `┘`
- Horizontal: `─` (thin, not thick `═`)
- Section divider: `├─────────────┤`
- Vertical: `│`

**Border Color:** Muted cyan (`ACCENT_CYAN`) for cohesive, minimal look

### Section Hierarchy

```
1. LOGO (geometric, centered)
2. SYSTEM (basic info)
3. HARDWARE (CPU, GPU, temp)
4. INFO (uptime, packages, shell)
5. NETWORK (IP, interfaces)
6. TIME (current time/date)
7. FOOTER (version, instructions)
```

### Column Layout

- **Box Left Margin**: 2 spaces
- **Label Column**: 26 characters
- **Value Column**: Dynamic, flexible
- **Right Margin**: 2 spaces
- **Total Width**: 76 characters (standard, fits most terminals)

---

## 📊 Data Presentation

### Progress Bars

**Flat Design:**
```
Memory      ▸▸▸▸▸▸▸░░░░░░░░░░  67%
CPU Load    ▸▸▸▸░░░░░░░░░░░░░░  25%
```

**Characters:**
- Filled: `▸` (right-pointing triangle)
- Empty: `▹` (outlined triangle)
- Length: 16 characters (optimal)

**Color Coding:**
- Memory: Purple
- CPU: Orange/Warm
- Disk: Orange
- Default: Based on context

---

## 🎯 Color Implementation Rules

### When to Use Each Color

| Element | Color | Reasoning |
|---------|-------|-----------|
| UI Borders | Cyan | Primary accent, high visibility |
| Section Headers | Label Gray | Subtle, readable |
| Data Values | Bright White | Emphasis, critical info |
| Status Indicators | Status Colors | Green/Orange/Red pattern |
| Warnings | Status_Warn | Orange for caution |
| Critical (temp >80°C) | Status_Crit | Red for urgent |
| Good (uptime, battery) | Status_OK | Green for positive |
| Memory/GPU | Purple | Specialized, memory-related |
| Network | Cyan | Matches primary accent |

### No Rainbow Colors
- ✗ Every line a different color
- ✓ Strategic use of 3-4 accent colors
- ✓ Monochromatic base with accents

---

## ✨ Features

### Intelligent Color Coding

- **Temperature alerts**: Green (good) → Orange (warm) → Red (hot)
- **VPN status**: Green (active) → Gray (inactive)
- **Resource usage**: Dynamic coloring based on thresholds

### Minimalist Information Density

- **Hidden N/A values**: No cluttering with unavailable data
- **Conditional sections**: GPU only shown if detected
- **Smart defaults**: Battery only shown if available

---

## 🎯 Testing & Validation

### Dark Terminal Compatibility

✓ Works on: Dracula, Nord, One Dark, Solarized Dark, Gruvbox Dark
✓ Tested on: GNOME, KDE Plasma, Sway, i3, XFCE

### Terminal Emulators

✓ Tested on: Alacritty, Kitty, GNOME Terminal, Konsole, Terminator, xterm

---

**Design Complete** ✨

Metetch now delivers a modern, professional terminal UI that rivals system fetch tools while maintaining superior performance and code simplicity.
