#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <ncurses.h>
#include <vector>
#include "data_types.h"
#include "utils.h"

using namespace std;

string configPath() {
    const char* home = getenv("HOME");
    if (!home) home = ".";
    string dir = string(home) + "/.config/metfetch";
    struct stat st;
    if (stat(dir.c_str(), &st) != 0) mkdir(dir.c_str(), 0700);
    return dir + "/config.ini";
}

void loadConfig() {
    ifstream f(configPath());
    if (!f.is_open()) return;
    string line;
    while (getline(f, line)) {
        if (line.empty() || line[0] == '#') continue;
        auto pos = line.find('=');
        if (pos == string::npos) continue;
        string k = line.substr(0, pos);
        string v = line.substr(pos+1);
        if (k == "show_realtime_in_os") cfg.show_realtime_in_os = (v == "1");
        else if (k == "show_gpu") cfg.show_gpu = (v == "1");
        else if (k == "show_disk") cfg.show_disk = (v == "1");
        else if (k == "theme") cfg.theme = v;
    }
}

void saveConfig() {
    ofstream f(configPath());
    if (!f.is_open()) return;
    f << "show_realtime_in_os=" << (cfg.show_realtime_in_os ? "1" : "0") << "\n";
    f << "show_gpu=" << (cfg.show_gpu ? "1" : "0") << "\n";
    f << "show_disk=" << (cfg.show_disk ? "1" : "0") << "\n";
    f << "theme=" << cfg.theme << "\n";
}

void configureMenu() {
    loadConfig();
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    vector<string> items = {
        "Show real-time in OS line",
        "Show GPU",
        "Show Disk",
        "Theme",
        "Save and Exit",
        "Exit without Saving"
    };
    int cur = 0;
    int n = (int)items.size();

    while (true) {
        clear();
        mvprintw(1, 2, "metfetch configuration — use Up/Down, Space toggle, Enter select");
        for (int i = 0; i < n; ++i) {
            if (i == cur) attron(A_REVERSE);
            mvprintw(3 + i, 4, "%s", items[i].c_str());
            if (i == 0) mvprintw(3 + i, 48, "%s", (cfg.show_realtime_in_os ? "ON" : "OFF"));
            if (i == 1) mvprintw(3 + i, 48, "%s", (cfg.show_gpu ? "ON" : "OFF"));
            if (i == 2) mvprintw(3 + i, 48, "%s", (cfg.show_disk ? "ON" : "OFF"));
            if (i == 3) mvprintw(3 + i, 48, "%s", cfg.theme.c_str());
            if (i == cur) attroff(A_REVERSE);
        }
        int ch = getch();
        if (ch == KEY_UP) cur = (cur - 1 + n) % n;
        else if (ch == KEY_DOWN) cur = (cur + 1) % n;
        else if (ch == ' ' || ch == 10) {
            if (cur == 0) cfg.show_realtime_in_os = !cfg.show_realtime_in_os;
            else if (cur == 1) cfg.show_gpu = !cfg.show_gpu;
            else if (cur == 2) cfg.show_disk = !cfg.show_disk;
            else if (cur == 3) {
                echo(); curs_set(1);
                mvprintw(10, 4, "Enter theme: ");
                char buf[128] = {0};
                getnstr(buf, sizeof(buf)-1);
                if (buf[0]) cfg.theme = string(buf);
                noecho(); curs_set(0);
            } else if (cur == 4) { saveConfig(); break; }
            else if (cur == 5) break;
        } else if (ch == 27) break;
    }

    endwin();
}
