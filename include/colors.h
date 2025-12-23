#pragma once

namespace colors {
    // ========== MODERN MINIMAL COLOR PALETTE ==========
    // Inspired by KDE Plasma 6 / Wayland dark themes
    // Designed for minimal, professional terminal aesthetics
    
    // PRIMARY ACCENT COLORS (thin borders, highlights)
    inline const char* ACCENT_CYAN   = "\033[38;5;51m";     // Bright cyan - primary UI
    inline const char* ACCENT_LIME   = "\033[38;5;118m";    // Lime green - success states
    inline const char* ACCENT_PURPLE = "\033[38;5;177m";    // Soft purple - secondary accent
    
    // TEXT COLORS
    inline const char* TEXT_BRIGHT   = "\033[38;5;231m";    // Bright white - main text
    inline const char* TEXT_MUTED    = "\033[38;5;244m";    // Dark gray - secondary text
    inline const char* TEXT_DIM      = "\033[38;5;238m";    // Very dark - subtle elements
    inline const char* TEXT_LABEL    = "\033[38;5;251m";    // Light gray - labels
    inline const char* TEXT_VALUE    = "\033[38;5;231m";    // Bright white - values
    
    // STATUS COLORS
    inline const char* STATUS_INFO   = "\033[38;5;39m";     // Deep blue - informational
    inline const char* STATUS_OK     = "\033[38;5;113m";    // Green - good/operational
    inline const char* STATUS_WARN   = "\033[38;5;208m";    // Orange - warnings
    inline const char* STATUS_CRIT   = "\033[38;5;196m";    // Red - critical alerts
    
    // SPECIALIZED COLORS
    inline const char* COLOR_CPU     = "\033[38;5;111m";    // Blue - CPU information
    inline const char* COLOR_MEM     = "\033[38;5;177m";    // Purple - Memory usage
    inline const char* COLOR_DISK    = "\033[38;5;214m";    // Orange - Disk/Storage
    inline const char* COLOR_NET     = "\033[38;5;51m";     // Cyan - Network stats
    inline const char* COLOR_TEMP    = "\033[38;5;208m";    // Orange - Temperature
    inline const char* COLOR_GPU     = "\033[38;5;177m";    // Purple - GPU information
    
    // TEXT STYLES
    inline const char* BOLD          = "\033[1m";
    inline const char* DIM_STYLE     = "\033[2m";
    inline const char* ITALIC        = "\033[3m";
    inline const char* RESET         = "\033[0m";
    
    // LEGACY ALIASES (for backward compatibility - will be phased out)
    inline const char* rst = RESET;
    inline const char* bld = BOLD;
    inline const char* dim = DIM_STYLE;
    inline const char* cy = ACCENT_CYAN;
    inline const char* b = COLOR_CPU;
    inline const char* y = TEXT_VALUE;
    inline const char* g = ACCENT_CYAN;
    inline const char* r = STATUS_CRIT;
    inline const char* w = TEXT_BRIGHT;
    inline const char* m = ACCENT_PURPLE;
    inline const char* pk = ACCENT_LIME;
    inline const char* p = ACCENT_PURPLE;
    inline const char* gry = TEXT_MUTED;
    inline const char* lgry = TEXT_DIM;
    inline const char* o = STATUS_WARN;}