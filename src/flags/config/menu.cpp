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
    
    // Add all registered features
    for (size_t i = 0; i < features.size(); ++i) {
        items.push_back({
            features[i].label,
            features[i].description,
            true,
            (int)i
        });
    }
    
    // Add theme selector
    items.push_back({
        "Theme Selector",
        "Choose color theme (default/dark/light/custom)",
        false,
        -1
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
    
    while (true) {
        clear();
        mvprintw(1, 2, "metetch configuration — use Up/Down, Space toggle, Enter select");
        mvprintw(2, 2, "Features: %d/%zu registered", (int)items.size() - 3, features.size());
        
        for (int i = 0; i < n; ++i) {
            if (i == cur) attron(A_REVERSE);
            mvprintw(4 + i, 4, "%-40s", items[i].label);
            
            if (items[i].is_feature) {
                bool status = features_registry.getFeatureStatus(features[items[i].feature_index].id);
                mvprintw(4 + i, 48, "%s", (status ? "ON" : "OFF"));
            } else if (items[i].feature_index == -1) {
                // Theme selector
                mvprintw(4 + i, 48, "[%s]", cfg.theme.c_str());
            }
            
            if (i == cur) attroff(A_REVERSE);
        }
        
        // Show description
        mvprintw(n + 6, 4, "Description: %s", items[cur].description);
        
        int ch = getch();
        if (ch == KEY_UP) cur = (cur - 1 + n) % n;
        else if (ch == KEY_DOWN) cur = (cur + 1) % n;
        else if (ch == ' ' || ch == 10) {
            if (items[cur].is_feature) {
                // Toggle feature
                features_registry.toggleFeature(features[items[cur].feature_index].id);
            } else if (items[cur].feature_index == -1) {
                // Theme selector
                echo();
                curs_set(1);
                mvprintw(n + 8, 4, "Enter theme (default/dark/light/custom): ");
                char buf[128] = {0};
                getnstr(buf, sizeof(buf) - 1);
                if (buf[0]) cfg.theme = string(buf);
                noecho();
                curs_set(0);
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
