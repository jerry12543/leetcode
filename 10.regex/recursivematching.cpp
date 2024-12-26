#include <iostream>
#include <string>
using namespace std;
auto isMatch(string s, string p) -> bool;
void editDups(string& p);
int main() {
    cout << isMatch("aaaaaaaaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*");
}

bool isMatch(string s, string p) {
    editDups(p);
    if (s.empty()) {
        if (p.empty()) {
            return true;
        }
        if (p[0] == '*') {
            return isMatch("", p.substr(1, p.size() - 1));
        }
        if (p.size() == 1) {
            return false;
        }
        if (p[1] == '*') {
            return isMatch(s, p.substr(2, p.size() - 2));
        }
        return false;
    }
    if (p.empty()) {
        return false;
    }
    if (s[0] != p[0] && p[0] != '.') {
        if (p.size() == 1) {
            return false;
        }
        if (p[0] == '*') {
            return isMatch(s, p.substr(1, p.size() - 1));
        }
        if (p[1] == '*') {
            return isMatch(s, p.substr(2, p.size() - 2));
        }
        return false;
    }
    if (p.size() == 1) {
        return s.size() == 1;
    }
    if (p[1] == '*') {
        if (isMatch(s.substr(1, s.size() - 1), p)) {
            return true;
        }
        if (isMatch(s.substr(1, s.size() - 1), p.substr(2, p.size() - 2))) {
            return true;
        }
        if (isMatch(s, p.substr(2, p.size() - 2))) {
            return true;
        }
        return false;
    }
    return isMatch(s.substr(1, s.size() - 1), p.substr(1, p.size() - 1));
}

void editDups(string& p) {
    // for (uint i = 0; i < p.size() - 4;) {
    for (uint32_t i = 0; i + 4 < p.size();) {
        if (i + 4 >= p.size()) {
            return;
        }
        if (p[i + 1] == '*') {
            size_t lastbeginind = i + 2;
            while (lastbeginind < p.size() - 1) {
                if (p[lastbeginind] != p[i] || p[lastbeginind + 1] != '*') {
                    break;
                }
                lastbeginind += 2;
            }
            if (lastbeginind > i + 2) {
                p = p.erase(i + 2, lastbeginind - (i + 2));
            }
            i += 2;
        } else {
            ++i;
        }
    }
}