/**
 * Interactive Configuration Menu
 * Fully modular with infinite customizable features
 */

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <string>
#include <cstring>
#include "data_types.h"
#include "flags/config/features_registry.h"
#include "theme_manager.h"

using namespace std;

extern Config cfg;
extern void loadConfig();
extern void saveConfig();
extern FeaturesRegistry features_registry;
extern void initializeFeaturesRegistry();

void showConfigMenu() {
    loadConfig();
    initializeFeaturesRegistry();
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    const auto& features = features_registry.getFeatures();
    
    // Menu structure: features + theme + save/exit options
    struct MenuItem {
        const char* label;
        const char* description;
        bool is_feature;
        int feature_index;
    };
    
    vector<MenuItem> items;
    
    // Add theme selector
    items.push_back({
        "Theme Selector",
        "Choose color theme (select from list)",
        false,
        -1
    });
    
    // Add preset editors
    items.push_back({
        "Edit Preset: Default",
        "Configure which features appear in the Default preset",
        false,
        -4
    });
    items.push_back({
        "Edit Preset: Minimal",
        "Configure which features appear in the Minimal preset",
        false,
        -5
    });
    items.push_back({
        "Edit Preset: Full",
        "Configure which features appear in the Full preset",
        false,
        -6
    });
    
    // Add save/exit options
    items.push_back({
        "Save and Exit",
        "Save configuration and return",
        false,
        -2
    });
    
    items.push_back({
        "Exit without Saving",
        "Discard changes and return",
        false,
        -3
    });
    
    int cur = 0;
    int n = (int)items.size();
    
    // helpers for presets
    auto splitCSV = [](const std::string &s) {
        std::vector<std::string> out;
        size_t start = 0;
        while (start < s.size()) {
            auto pos = s.find(',', start);
            if (pos == std::string::npos) pos = s.size();
            if (pos > start) out.push_back(s.substr(start, pos - start));
            start = pos + 1;
        }
        return out;
    };

    auto csvContains = [&](const std::string &csv, const std::string &id)->bool{
        auto v = splitCSV(csv);
        for (auto &x : v) if (x == id) return true;
        return false;
    };

    auto csvToggle = [&](std::string &csv, const std::string &id, bool present) {
        auto v = splitCSV(csv);
        std::vector<std::string> nv;
        for (auto &x : v) if (x.size() && x != id) nv.push_back(x);
        if (present) nv.push_back(id);
        // rebuild
        std::string out;
        for (size_t i = 0; i < nv.size(); ++i) {
            if (i) out += ",";
            out += nv[i];
        }
        csv = out;
    };

    while (true) {
        clear();
        mvprintw(1, 2, "metetch configuration — use Up/Down, Enter to edit, Esc to exit");
        mvprintw(2, 2, "Presets: Theme + 3 Presets (Default, Minimal, Full)");
        
        for (int i = 0; i < n; ++i) {
            if (i == cur) attron(A_REVERSE);
            mvprintw(4 + i, 4, "%-40s", items[i].label);
            
            if (items[i].is_feature) {
                bool status = features_registry.getFeatureStatus(features[items[i].feature_index].id);
                mvprintw(4 + i, 48, "%s", (status ? "ON" : "OFF"));
            } else if (items[i].feature_index == -1) {
                // Theme selector
                mvprintw(4 + i, 48, "[%s]", cfg.theme.c_str());
            } else if (items[i].feature_index == -4) {
                int count = splitCSV(cfg.preset_default).size();
                mvprintw(4 + i, 48, "[%d/%zu items]", (count == 0 ? 0 : count), features.size());
            } else if (items[i].feature_index == -5) {
                int count = splitCSV(cfg.preset_minimal).size();
                mvprintw(4 + i, 48, "[%d/%zu items]", (count == 0 ? 0 : count), features.size());
            } else if (items[i].feature_index == -6) {
                int count = splitCSV(cfg.preset_full).size();
                mvprintw(4 + i, 48, "[%d/%zu items]", (count == 0 ? 0 : count), features.size());
            }
            
            if (i == cur) attroff(A_REVERSE);
        }
        
        // Show description
        mvprintw(n + 6, 4, "Description: %s", items[cur].description);
        
        int ch = getch();
        if (ch == KEY_UP) cur = (cur - 1 + n) % n;
        else if (ch == KEY_DOWN) cur = (cur + 1) % n;
        else if (ch == 10) { // Enter -> edit/select
            if (items[cur].is_feature) {
                // Enter edit mode for feature: show current ON/OFF and let arrows switch, Enter to confirm
                const char* fid = features[items[cur].feature_index].id;
                bool current = features_registry.getFeatureStatus(fid);
                int sel = current ? 1 : 0; // 0=OFF,1=ON
                while (true) {
                    mvprintw(n + 8, 4, "Set %s: Use Left/Right or Up/Down to change, Enter to confirm, Esc to cancel", features[items[cur].feature_index].label);
                    if (sel == 0) attron(A_REVERSE);
                    mvprintw(n + 10, 6, "OFF");
                    if (sel == 0) attroff(A_REVERSE);
                    if (sel == 1) attron(A_REVERSE);
                    mvprintw(n + 10, 12, "ON");
                    if (sel == 1) attroff(A_REVERSE);
                    int mch = getch();
                    if (mch == KEY_LEFT || mch == KEY_UP) sel = (sel - 1 + 2) % 2;
                    else if (mch == KEY_RIGHT || mch == KEY_DOWN) sel = (sel + 1) % 2;
                    else if (mch == 10) {
                        bool want = (sel == 1);
                        // set via pointer to avoid toggling wrong number of times
                        auto *feat = features_registry.getFeatureById(features[items[cur].feature_index].id);
                        if (feat && feat->toggle_ptr) {
                            *feat->toggle_ptr = want;
                            if (feat->on_toggle) feat->on_toggle();
                        }
                        break;
                    } else if (mch == 27) break;
                }
            } else if (items[cur].feature_index == -1) {
                // Theme selector - present a list of available themes (Enter to enter, arrows to move, Enter to confirm)
                auto themes = availableThemes();
                int tcur = 0;
                while (true) {
                    mvprintw(n + 8, 4, "Select theme (Use Up/Down, Enter to choose, Esc to cancel):");
                    for (int ti = 0; ti < (int)themes.size(); ++ti) {
                        if (ti == tcur) attron(A_REVERSE);
                        mvprintw(n + 10 + ti, 6, "%s", themes[ti].c_str());
                        if (ti == tcur) attroff(A_REVERSE);
                    }
                    int tch = getch();
                    if (tch == KEY_UP) tcur = (tcur - 1 + (int)themes.size()) % (int)themes.size();
                    else if (tch == KEY_DOWN) tcur = (tcur + 1) % (int)themes.size();
                    else if (tch == 10) { // Enter
                        cfg.theme = themes[tcur];
                        applyTheme(cfg.theme);
                        break;
                    } else if (tch == 27) {
                        break;
                    }
                }
            } else if (items[cur].feature_index == -4 || items[cur].feature_index == -5 || items[cur].feature_index == -6) {
                // Preset editor
                std::string *presetPtr = nullptr;
                if (items[cur].feature_index == -4) presetPtr = &cfg.preset_default;
                else if (items[cur].feature_index == -5) presetPtr = &cfg.preset_minimal;
                else if (items[cur].feature_index == -6) presetPtr = &cfg.preset_full;
                if (presetPtr) {
                    int pcur = 0;
                    while (true) {
                        clear();
                        mvprintw(1,2, "Editing preset: %s", items[cur].label);
                        mvprintw(2,2, "Use Up/Down to navigate features, Enter to toggle inclusion, s to save, Esc to cancel/back");
                        for (int i = 0; i < (int)features.size(); ++i) {
                            bool included = csvContains(*presetPtr, features[i].id);
                            if (i == pcur) attron(A_REVERSE);
                            mvprintw(4 + i, 4, "[%c] %-40s", (included ? 'x' : ' '), features[i].label);
                            if (i == pcur) attroff(A_REVERSE);
                        }
                        int pch = getch();
                        if (pch == KEY_UP) pcur = (pcur - 1 + (int)features.size()) % (int)features.size();
                        else if (pch == KEY_DOWN) pcur = (pcur + 1) % (int)features.size();
                        else if (pch == 10) {
                            // toggle inclusion
                            bool included = csvContains(*presetPtr, features[pcur].id);
                            csvToggle(*presetPtr, features[pcur].id, !included);
                        } else if (pch == 's' || pch == 'S') {
                            // save and break
                            saveConfig();
                            break;
                        } else if (pch == 27) break;
                    }
                }
            } else if (items[cur].feature_index == -2) {
                // Save and exit
                saveConfig();
                break;
            } else if (items[cur].feature_index == -3) {
                // Exit without saving
                break;
            }
        } else if (ch == 27) break;  // ESC
    }

    endwin();
}
