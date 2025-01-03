#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    static auto isMatch(string const& s, string const& p) -> bool {
        vector<bool> dp(p.length() + 1);
        // base cases
        dp[0] = true;
        for (size_t i = 1; i < p.length() && p[i] == '*'; i += 2) {
            dp[i + 1] = true;
        }
        // loop through increasingly long prefixes of s
        for (char const currchar : s) {
            bool prevMatchesWithoutLast = dp[0];
            dp[0] = false;
            // check against increasingly long prefixes of p
            for (size_t pind = 0; pind < p.length(); ++pind) {
                bool const temp = dp[pind + 1];
                if (p[pind] == '*') {   // case 1
                    dp[pind + 1] = dp[pind - 1] || (dp[pind + 1] && (currchar == p[pind - 1] || p[pind - 1] == '.'));
                } else {   // case 2
                    dp[pind + 1] = prevMatchesWithoutLast && (currchar == p[pind] || p[pind] == '.');
                }
                // string prefix without currchar matches the pattern prefix without the last character
                prevMatchesWithoutLast = temp;
            }
        }
        return dp[p.length()];
    }
};