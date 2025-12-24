# Metetch Color Palette & Design Guide

## 🎨 Complete Color Reference

### ANSI 256-Color Codes Used

```
PRIMARY ACCENTS
├─ ACCENT_CYAN   #00ffff  (51)   Bright cyan - primary borders
├─ ACCENT_PURPLE #d787ff  (177)  Soft purple - memory, GPU
└─ ACCENT_LIME   #87ff00  (118)  Bright green - success states

TEXT COLORS
├─ TEXT_BRIGHT   #ffffff  (231)  Bright white - main text
├─ TEXT_LABEL    #dadada  (251)  Light gray - labels
├─ TEXT_MUTED    #808080  (244)  Dark gray - secondary text
└─ TEXT_DIM      #3a3a3a  (238)  Very dark - subtle elements

STATUS COLORS
├─ STATUS_OK     #87d787  (113)  Green - good states
├─ STATUS_WARN   #ffaf00  (208)  Orange - warnings
├─ STATUS_CRIT   #ff0000  (196)  Red - critical alerts
└─ STATUS_INFO   #0087ff  (39)   Blue - information

SPECIALIZED COLORS
├─ COLOR_CPU     #5787d7  (111)  Blue - CPU info
├─ COLOR_MEM     #d787ff  (177)  Purple - Memory
├─ COLOR_DISK    #ffaf00  (214)  Orange - Disk
├─ COLOR_NET     #00ffff  (51)   Cyan - Network
├─ COLOR_TEMP    #ffaf00  (208)  Orange - Temperature
└─ COLOR_GPU     #d787ff  (177)  Purple - GPU
```

## Runtime UI Mapping (current defaults)

- Box borders (┌ ─ ┐ │ └ ┘): Cyan
- Icons: Cyan
- Labels: Cyan
- Values: White
- Header separator (━): Cyan
- Version line: Magenta

These mappings are the default theme and can be changed at runtime via the `--config` theme selector. The theme manager controls the underlying ANSI color codes but follows the mapping above by default.

---

## 🎨 Design Elements

### Geometric Logo (Canonical)

Use the canonical header/brand block below as the geometric logo shown in the app and documentation:

```
								 _       _       _     
	_ __ ___   ___| |_ ___| |_ ___| |__  
 | '_ ` _ \ / _ \ __/ _ \ __/ __| '_ \ 
 | | | | | |  __/ ||  __/ || (__| | | |
 |_| |_| |_|\___|\__\___|\__\___|_| |_|

	📦 metetch 0.5.4  |  🐙 github.com/techoraye
	─────────────────────────────────────────────
```

This is the canonical ASCII header used across the README, release notes, and rendered output. The color mapping for runtime UI is:

- Box borders (┌ ─ ┐ │ └ ┘): Cyan
- Icons: Cyan
- Labels: Cyan
- Values: White
- Header separator (━): Cyan
- Version line: Magenta

These defaults are controlled by the theme manager and can be changed at runtime via `--config`.

---

## 🖥️ Terminal Compatibility

### Tested & Working

| Terminal | OS | Color Support | Unicode | Status |
|----------|----|----|---------|--------|
| Alacritty | All | 256 | ✓ | Perfect |
| Kitty | All | 256+ | ✓ | Perfect |
| Konsole | Linux | 256 | ✓ | Perfect |
| Gnome Terminal | Linux | 256 | ✓ | Perfect |
| Terminator | Linux | 256 | ✓ | Perfect |
| Sway/Wayland | Linux | 256 | ✓ | Perfect |

### Dark Theme Compatibility

**Tested on:**
- ✓ Dracula
- ✓ Nord
- ✓ One Dark Pro
- ✓ Gruvbox Dark
- ✓ Solarized Dark
- ✓ Catppuccin
- ✓ Tokyo Night

---

## 📊 Progress Bar Styles

### Flat Design (Current)

```
Memory  ▸▸▸▸▸▸▸░░░░░░░░░░  67%
CPU     ▸▸▸▸░░░░░░░░░░░░░░  25%
Disk    ▸▸▸▸▸▸▸▸▸▸▸▸░░░░░░  75%
```

**Characters:**
- Filled: `▸` (right-pointing triangle - feel)
- Empty: `▹` (outlined triangle - minimal)
- Length: 16 characters (optimal for 76-char width)

---

## 🎯 Design Decisions

### Why Thin Borders Over Thick?

```
Old (retro, thick):
╔════════════════╗  ← Too heavy, dated
║ Content        ║
╚════════════════╝

New (modern, thin):
┌────────────────┐  ← Clean, professional
│ Content        │
└────────────────┘
```

### Why Geometric Logo Over Text?

```
Old (text-based):
███████████████████████
█ METETCH
███████████████████████

New (geometric):
╭─ ◇ ─────────────────╮
│  ┏━━━┓ Digital       │
│  ┃   ┃ Blueprint     │
╰─ ◇ ─────────────────╯
```

- **Scalable**: Looks good at any size
- **Modern**: Not retro/dated
- **Professional**: Suitable for screenshots
- **Memorable**: Distinctive visual identity

### Why 76-Character Width?

Perfect balance between readability and space usage. Works on all standard terminals.

---

**Design Reference Complete** ✨
