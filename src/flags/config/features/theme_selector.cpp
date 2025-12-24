/**
 * Theme Selector Feature
 * Allows users to select color theme
 */

#include <string>
#include "data_types.h"
#include "theme_manager.h"

using namespace std;

void selectTheme(const string& theme_name) {
    cfg.theme = theme_name;
    applyTheme(theme_name);
}

string getCurrentTheme() {
    return cfg.theme;
}

const char* getThemeSelectorLabel() {
    return "Color Theme";
}

const char* getThemeSelectorDescription() {
    return "Select color theme from available list";
}
