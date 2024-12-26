#include <iostream>
#include <string>
using namespace std;

auto intToRoman(int num) -> string;
auto main() -> int {
    int const toConvert = 3765;
    cout << intToRoman(toConvert);
}
// Assumes 1 <= num <= 3999
auto intToRoman(int num) -> string {
    vector<char> symbols = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };

    string soln;
    string n = to_string(num);
    size_t lower = 0;
    for (size_t i = 0; i < n.size(); ++i) {
        lower = 2 * (n.size() - (i + 1));
        if (n[i] == '9' || n[i] == '4') {
            soln += symbols[lower];
            if (n[i] == '9') {
                soln += symbols[lower + 2];
            } else if (n[i] == '4') {
                soln += symbols[lower + 1];
            }
        } else {
            int toAdd = 0;
            if (n[i] >= '5') {
                soln += symbols[lower + 1];
                toAdd = n[i] - '5';
            } else {
                toAdd = n[i] - '0';
            }
            for (int i = 0; i < toAdd; ++i) {
                soln += symbols[lower];
            }
        }
    }
    return soln;
}