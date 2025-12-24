/**
 * Theme manager - provides runtime theme switching for ANSI colors
 */

#include "theme_manager.h"
#include "colors.h"
#include <string>
#include <vector>

using namespace std;

static vector<string> themes = {
    "default",
    "dark",
    "light",
    "magenta",
    "solarized",
    "sunset",
    "ocean",
    "midnight",
    "nebula",
    "ember",
    "forest",
    "arcane",
    "glacier",
    "retro",
    "matrix",
    "monokai",
    "copper"
};

vector<string> availableThemes() { return themes; }

string getCurrentTheme() {
    // simple fallback if not set elsewhere
    return string("default");
}

void applyTheme(const string &name) {
    // map theme to ANSI codes (simple palettes)
    if (name == "dark" || name == "default") {
        // BRIGHT, HIGHLY VISIBLE colors for dark terminals (improves contrast)
        colors::ACCENT_CYAN = "\033[38;5;87m";      // brighter cyan
        colors::ACCENT_MAGENTA = "\033[38;5;213m";  // brighter magenta
        colors::ACCENT_LIME = "\033[38;5;154m";     // brighter lime
        colors::ACCENT_PURPLE = "\033[38;5;183m";   // brighter purple
        colors::TEXT_LABEL = "\033[38;5;255m";      // bright white labels
        colors::TEXT_VALUE = "\033[38;5;231m";      // bright white values
        colors::TEXT_MUTED = "\033[38;5;243m";      // muted gray
        colors::STATUS_OK = "\033[38;5;120m";       // bright green
        colors::STATUS_WARN = "\033[38;5;220m";     // bright yellow
        colors::STATUS_CRIT = "\033[38;5;203m";     // bright red
    } else if (name == "light") {
        colors::ACCENT_CYAN = "\033[38;5;25m";
        colors::ACCENT_MAGENTA = "\033[38;5;161m";
        colors::ACCENT_LIME = "\033[38;5;34m";
        colors::ACCENT_PURPLE = "\033[38;5;99m";
        colors::TEXT_LABEL = "\033[38;5;236m";
        colors::TEXT_VALUE = "\033[38;5;16m";
        colors::STATUS_OK = "\033[38;5;34m";
        colors::STATUS_WARN = "\033[38;5;130m";
        colors::STATUS_CRIT = "\033[38;5;160m";
    } else if (name == "magenta") {
        colors::ACCENT_CYAN = "\033[38;5;201m";
        colors::ACCENT_MAGENTA = "\033[38;5;201m";
        colors::ACCENT_LIME = "\033[38;5;118m";
        colors::ACCENT_PURPLE = "\033[38;5;171m";
        colors::TEXT_LABEL = "\033[38;5;251m";
        colors::TEXT_VALUE = "\033[38;5;231m";
        colors::STATUS_OK = "\033[38;5;113m";
        colors::STATUS_WARN = "\033[38;5;208m";
        colors::STATUS_CRIT = "\033[38;5;196m";
    } else if (name == "solarized") {
        colors::ACCENT_CYAN = "\033[38;5;37m";
        colors::ACCENT_MAGENTA = "\033[38;5;174m";
        colors::ACCENT_LIME = "\033[38;5;108m";
        colors::ACCENT_PURPLE = "\033[38;5;141m";
        colors::TEXT_LABEL = "\033[38;5;244m";
        colors::TEXT_VALUE = "\033[38;5;230m";
        colors::STATUS_OK = "\033[38;5;108m";
        colors::STATUS_WARN = "\033[38;5;178m";
        colors::STATUS_CRIT = "\033[38;5;167m";
    } else if (name == "sunset") {
        colors::ACCENT_CYAN = "\033[38;5;208m";
        colors::ACCENT_MAGENTA = "\033[38;5;204m";
        colors::ACCENT_LIME = "\033[38;5;220m";
        colors::ACCENT_PURPLE = "\033[38;5;160m";
        colors::TEXT_LABEL = "\033[38;5;248m";
        colors::TEXT_VALUE = "\033[38;5;231m";
        colors::STATUS_OK = "\033[38;5;112m";
        colors::STATUS_WARN = "\033[38;5;214m";
        colors::STATUS_CRIT = "\033[38;5;203m";
    } else if (name == "ocean") {
        colors::ACCENT_CYAN = "\033[38;5;39m";
        colors::ACCENT_MAGENTA = "\033[38;5;141m";
        colors::ACCENT_LIME = "\033[38;5;120m";
        colors::ACCENT_PURPLE = "\033[38;5;117m";
        colors::TEXT_LABEL = "\033[38;5;250m";
        colors::TEXT_VALUE = "\033[38;5;231m";
        colors::STATUS_OK = "\033[38;5;112m";
        colors::STATUS_WARN = "\033[38;5;226m";
        colors::STATUS_CRIT = "\033[38;5;196m";
    }

    else if (name == "midnight") {
        colors::ACCENT_CYAN = "\033[38;5;75m";
        colors::ACCENT_MAGENTA = "\033[38;5;139m";
        colors::ACCENT_LIME = "\033[38;5;120m";
        colors::ACCENT_PURPLE = "\033[38;5;111m";
        colors::TEXT_LABEL = "\033[38;5;255m";
        colors::TEXT_VALUE = "\033[38;5;231m";
        colors::STATUS_OK = "\033[38;5;112m";
        colors::STATUS_WARN = "\033[38;5;184m";
        colors::STATUS_CRIT = "\033[38;5;203m";
    } else if (name == "nebula") {
        colors::ACCENT_CYAN = "\033[38;5;81m";
        colors::ACCENT_MAGENTA = "\033[38;5;165m";
        colors::ACCENT_LIME = "\033[38;5;154m";
        colors::ACCENT_PURPLE = "\033[38;5;141m";
        colors::TEXT_LABEL = "\033[38;5;255m";
        colors::TEXT_VALUE = "\033[38;5;231m";
        colors::STATUS_OK = "\033[38;5;120m";
        colors::STATUS_WARN = "\033[38;5;220m";
        colors::STATUS_CRIT = "\033[38;5;196m";
    } else if (name == "ember") {
        colors::ACCENT_CYAN = "\033[38;5;208m";
        colors::ACCENT_MAGENTA = "\033[38;5;161m";
        colors::ACCENT_LIME = "\033[38;5;214m";
        colors::ACCENT_PURPLE = "\033[38;5;160m";
        colors::TEXT_LABEL = "\033[38;5;250m";
        colors::TEXT_VALUE = "\033[38;5;231m";
        colors::STATUS_OK = "\033[38;5;112m";
        colors::STATUS_WARN = "\033[38;5;214m";
        colors::STATUS_CRIT = "\033[38;5;203m";
    } else if (name == "forest") {
        colors::ACCENT_CYAN = "\033[38;5;29m";
        colors::ACCENT_MAGENTA = "\033[38;5;93m";
        colors::ACCENT_LIME = "\033[38;5;114m";
        colors::ACCENT_PURPLE = "\033[38;5;71m";
        colors::TEXT_LABEL = "\033[38;5;250m";
        colors::TEXT_VALUE = "\033[38;5;231m";
        colors::STATUS_OK = "\033[38;5;112m";
        colors::STATUS_WARN = "\033[38;5;178m";
        colors::STATUS_CRIT = "\033[38;5;160m";
    } else if (name == "arcane") {
        colors::ACCENT_CYAN = "\033[38;5;99m";
        colors::ACCENT_MAGENTA = "\033[38;5;171m";
        colors::ACCENT_LIME = "\033[38;5;154m";
        colors::ACCENT_PURPLE = "\033[38;5;177m";
        colors::TEXT_LABEL = "\033[38;5;255m";
        colors::TEXT_VALUE = "\033[38;5;231m";
        colors::STATUS_OK = "\033[38;5;112m";
        colors::STATUS_WARN = "\033[38;5;220m";
        colors::STATUS_CRIT = "\033[38;5;203m";
    } else if (name == "glacier") {
        colors::ACCENT_CYAN = "\033[38;5;111m";
        colors::ACCENT_MAGENTA = "\033[38;5;141m";
        colors::ACCENT_LIME = "\033[38;5;159m";
        colors::ACCENT_PURPLE = "\033[38;5;117m";
        colors::TEXT_LABEL = "\033[38;5;255m";
        colors::TEXT_VALUE = "\033[38;5;231m";
        colors::STATUS_OK = "\033[38;5;112m";
        colors::STATUS_WARN = "\033[38;5;153m";
        colors::STATUS_CRIT = "\033[38;5;161m";
    } else if (name == "retro") {
        colors::ACCENT_CYAN = "\033[38;5;51m";
        colors::ACCENT_MAGENTA = "\033[38;5;167m";
        colors::ACCENT_LIME = "\033[38;5;118m";
        colors::ACCENT_PURPLE = "\033[38;5;130m";
        colors::TEXT_LABEL = "\033[38;5;250m";
        colors::TEXT_VALUE = "\033[38;5;231m";
        colors::STATUS_OK = "\033[38;5;112m";
        colors::STATUS_WARN = "\033[38;5;214m";
        colors::STATUS_CRIT = "\033[38;5;160m";
    } else if (name == "matrix") {
        colors::ACCENT_CYAN = "\033[38;5;46m";
        colors::ACCENT_MAGENTA = "\033[38;5;82m";
        colors::ACCENT_LIME = "\033[38;5;118m";
        colors::ACCENT_PURPLE = "\033[38;5;34m";
        colors::TEXT_LABEL = "\033[38;5;255m";
        colors::TEXT_VALUE = "\033[38;5;231m";
        colors::STATUS_OK = "\033[38;5;112m";
        colors::STATUS_WARN = "\033[38;5;226m";
        colors::STATUS_CRIT = "\033[38;5;196m";
    } else if (name == "monokai") {
        colors::ACCENT_CYAN = "\033[38;5;80m";
        colors::ACCENT_MAGENTA = "\033[38;5;175m";
        colors::ACCENT_LIME = "\033[38;5;154m";
        colors::ACCENT_PURPLE = "\033[38;5;141m";
        colors::TEXT_LABEL = "\033[38;5;250m";
        colors::TEXT_VALUE = "\033[38;5;231m";
        colors::STATUS_OK = "\033[38;5;112m";
        colors::STATUS_WARN = "\033[38;5;214m";
        colors::STATUS_CRIT = "\033[38;5;203m";
    } else if (name == "copper") {
        colors::ACCENT_CYAN = "\033[38;5;166m";
        colors::ACCENT_MAGENTA = "\033[38;5;173m";
        colors::ACCENT_LIME = "\033[38;5;130m";
        colors::ACCENT_PURPLE = "\033[38;5;166m";
        colors::TEXT_LABEL = "\033[38;5;250m";
        colors::TEXT_VALUE = "\033[38;5;231m";
        colors::STATUS_OK = "\033[38;5;178m";
        colors::STATUS_WARN = "\033[38;5;214m";
        colors::STATUS_CRIT = "\033[38;5;160m";
    }
}
