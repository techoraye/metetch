#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <curl/curl.h>
#include "data_types.h"
#include "utils.h"

using namespace std;

// Global instances
Live lv;
Config cfg;
Layout lay;
const string ver = "0.5.0";
const string repo = "techoraye/metetch";
const string api = "https://api.github.com/repos/techoraye/metetch/releases/latest";
const string bin = "https://github.com/techoraye/metfetch/releases/latest/download/metetch";

size_t wcb(void* cont, size_t sz, size_t n, string* u) {
    u->append((char*)cont, sz * n);
    return sz * n;
}

string httpGet(const string& url) {
    CURL* curl = curl_easy_init();
    if (!curl) return "";
    string resp;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, wcb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "metfetch");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return (res == CURLE_OK) ? resp : "";
}

bool downloadFile(const string& url, const string& out) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;
    FILE* fp = fopen(out.c_str(), "wb");
    if (!fp) { curl_easy_cleanup(curl); return false; }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(fp);
    return res == CURLE_OK;
}

string extractVer(const string& json) {
    size_t pos = json.find("\"tag_name\":");
    if (pos == string::npos) return "";
    pos = json.find("\"", pos + 11);
    if (pos == string::npos) return "";
    size_t end = json.find("\"", pos + 1);
    if (end == string::npos) return "";
    string v = json.substr(pos + 1, end - pos - 1);
    if (!v.empty() && v[0] == 'v') v = v.substr(1);
    return v;
}

bool isNewer(const std::string& cur, const std::string& latest) {
    int ca=0, cb=0, cc=0;
    int la=0, lb=0, lc=0;
    sscanf(cur.c_str(), "%d.%d.%d", &ca, &cb, &cc);
    sscanf(latest.c_str(), "%d.%d.%d", &la, &lb, &lc);
    if (la != ca) return la > ca;
    if (lb != cb) return lb > cb;
    return lc > cc;
}

string ex(const string& cmd) {
    char buf[256];
    string res;
    FILE* p = popen((cmd + " 2>/dev/null").c_str(), "r");
    if (!p) return "";
    while (fgets(buf, sizeof(buf), p)) res += buf;
    pclose(p);
    if (!res.empty() && res.back() == '\n') res.pop_back();
    return res;
}

void ac(char ch, int d) {
    cout << ch << flush;
    this_thread::sleep_for(chrono::microseconds(d));
}

void al(const string& s, int d) {
    for (char ch : s) ac(ch, d);
}
