#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    static auto isMatch(string const& s, string const& p) -> bool {
        vector<bool> prev(p.length() + 1);
        vector<bool> curr(p.length() + 1);
        // base cases
        prev[0] = true;
        for (size_t i = 1; i < p.length() && p[i] == '*'; i += 2) {
            prev[i] = true;
            prev[i + 1] = true;
        }
        // loop through increasingly long prefixes of s
        for (char const currchar : s) {
            fill(curr.begin(), curr.end(), false);
            // check s prefix against increasingly long prefixes of p
            for (size_t pind = 0; pind < p.length(); ++pind) {
                if (currchar == p[pind] || p[pind] == '.') { // case 1
                    curr[pind + 1] = prev[pind];
                } else if (p[pind] == '*') { // case 2
                    curr[pind + 1]
                      = curr[pind - 1]                                                         // match with none
                     || (prev[pind + 1] && (currchar == p[pind - 1] || p[pind - 1] == '.'));   // match with 1+
                }
            }
            swap(curr, prev);
        }
        return prev[p.length()];
    }
};
