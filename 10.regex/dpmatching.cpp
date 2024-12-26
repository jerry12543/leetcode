#include <iostream>
#include <numeric>
#include <string>
using namespace std;
void editDups(string& p);
bool isMatch(string s, string p);
int main() {
    cout << isMatch("ab", ".*c");
}

bool isMatch(string s, string p) {
    editDups(p);
    vector<vector<bool>> tableau(s.size() + 1, vector<bool>(p.size() + 1, false));

    // fill in all equivalent to empties
    tableau[0][0] = true;
    for (uint i = 0; i < p.size(); ++i) {
        if (p[i] == '*') {
            tableau[0][i + 1] = tableau[0][i];   // only set to true
        } else if (i == p.size() - 1) {
            // tableau[0][i + 1] = false;
            break;
        } else if (p[i + 1] == '*') {
            tableau[0][i + 1] = tableau[0][i];   // only set to true
            tableau[0][i + 2] = tableau[0][i];
            ++i;
        } else {
            // tableau[0][i + 1] = false;
            break;
        }
    }
    for (uint sind = 0; sind < s.size(); ++sind) {
        for (uint pind = 0; pind < p.size(); ++pind) {
            if (s[sind] != p[pind] && p[pind] != '.') {
                if (pind != p.size() - 1) {
                    if (p[pind] == '*') {
                        tableau[sind + 1][pind + 1] = tableau[sind + 1][pind];
                    } else if (p[pind + 1] == '*') {
                        tableau[sind + 1][pind + 1] = tableau[sind + 1][pind];
                        tableau[sind + 1][pind + 2] = tableau[sind + 1][pind];
                        ++pind;
                    } else {
                        tableau[sind + 1][pind + 1] = false;
                        // break;
                    }
                }
            } else {
                if (pind == p.size() - 1) {
                    tableau[sind + 1][pind + 1] = tableau[sind][pind] && (sind == s.size() - 1);
                } else if (p[pind + 1] == '*') {
                    tableau[sind + 1][pind + 1]
                      = (tableau[sind][pind + 1] || tableau[sind][pind] || tableau[sind + 1][pind]);
                    tableau[sind + 1][pind + 2] = tableau[sind + 1][pind + 1];
                    ++pind;
                } else {
                    tableau[sind + 1][pind + 1] = tableau[sind][pind];
                }
            }
        }
    }
    for (auto& a : tableau) {
        for (auto b : a) {
            cout << b << ' ';
        }
        cout << endl;
    }
    return tableau[s.size()][p.size()];
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