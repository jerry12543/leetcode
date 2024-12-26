
// Note that someTrue makes the program slower in the worst case
#include <iostream>
#include <new>
#include <numeric>
#include <string>
using namespace std;
void editDups(string& p);
auto isMatch(string s, string p) -> bool;
auto main() -> int {
    cout << isMatch("aaaaaaaaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*");
}
auto isMatch(string s, string p) -> bool {
    editDups(p);
    vector<bool> prev(p.size() + 1, false);
    prev[0] = true;
    for (uint i = 0; i < p.size(); ++i) {
        if (p[i] == '*') {
            prev[i + 1] = prev[i];   // only set to true
        } else if (i == p.size() - 1) {
            // prev[i + 1] = false;
            break;
        } else if (p[i + 1] == '*') {
            prev[i + 1] = prev[i];   // only set to true
            prev[i + 2] = prev[i];
            ++i;
        } else {
            // prev[i + 1] = false;
            break;
        }
    }

    vector<bool> curr(p.size() + 1, false);

    for (uint sind = 0; sind < s.size(); ++sind) {
        bool someTrue = false;
        for (uint pind = 0; pind < p.size(); ++pind) {
            if (s[sind] != p[pind] && p[pind] != '.') {
                if (pind != p.size() - 1) {
                    if (p[pind] == '*') {
                        curr[pind + 1] = curr[pind];
                    } else if (p[pind + 1] == '*') {
                        curr[pind + 1] = curr[pind];
                        curr[pind + 2] = curr[pind];
                        ++pind;
                    } else {
                        curr[pind + 1] = false;
                    }
                } else {
                    curr[pind + 1] = false;
                }
            } else {
                if (pind == p.size() - 1) {
                    curr[pind + 1] = prev[pind] && (sind == s.size() - 1);
                } else if (p[pind + 1] == '*') {
                    curr[pind + 1] = (prev[pind + 1] || prev[pind] || curr[pind]);
                    curr[pind + 2] = curr[pind + 1];
                    ++pind;
                } else {
                    curr[pind + 1] = prev[pind];
                }
                someTrue = someTrue || curr[pind + 1];
            }
        }
        if (!someTrue) {
            return false;
        }
        prev.swap(curr);
        curr[0] = false;
    }
    return prev[p.size()];
}

void editDups(string& p) {
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