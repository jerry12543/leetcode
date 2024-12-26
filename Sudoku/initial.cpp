#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int const boardsize = 9;

template <typename T>
auto operator<<(ostream& os, vector<T> const& vec) -> ostream& {
    for (T const i : vec) {
        os << i << " ";
    }
    return os;
}
template <typename T>
auto operator<<(ostream& os, vector<vector<T>> const& vec) -> ostream& {
    for (auto const& i : vec) {
        cout << i << endl;
    }
    return os;
}


class Solution {
    // vector<int> possible;
    int possible;

    std::vector<std::vector<char>>* boardPtr;

    vector<unordered_map<int, bool>> rows;
    vector<vector<bool>> cols;
    vector<vector<bool>> squares;

public:
    static auto calcsquare(int row, int col) -> int { return ((row / 3) * 3) + (col / 3); }

    auto initContainers() -> void {
        unordered_map<int, bool> templ;
        templ.reserve(boardsize);
        for (int i = 1; i <= boardsize; ++i) {
            templ.emplace(i, false);
        }
        rows.resize(boardsize, templ);
        cols.resize(boardsize, vector<bool>(boardsize + 1));
        squares.resize(boardsize, vector<bool>(boardsize + 1));
    }

    // if there is only one single possible number, fills in the square
    auto fillSinglePossible(int row, int col) -> void {
        possible = -1;
        vector<bool>& currsquare = squares[calcsquare(row, col)];
        for (auto& iter : rows[row]) {
            if (!currsquare[iter.first] and !cols[col][iter.first]) {
                if (possible != -1) {
                    return;
                }
                possible = iter.first;
            }
        }
        currsquare[possible] = true;
        cols[col][possible] = true;
        rows[row].erase(possible);
        (*boardPtr)[row][col] = '0' + possible;
        cout << (*boardPtr)[row][col] << " inserted at row " << row << " col " << col << endl;
    }


    auto checkAllSingles() -> bool {
        vector<vector<char>>& board = *boardPtr;
        for (int row = 0; row < boardsize; ++row) {
            for (int col = 0; col < boardsize; ++col) {
                if (board[row][col] == '.') {
                    fillSinglePossible(row, col);
                }
            }
        }
        return std::any_of(rows.begin(), rows.end(),
                           [](std::unordered_map<int, bool> const& map) -> bool { return !map.empty(); });
    }

    void solveSudoku(std::vector<std::vector<char>>* boardIn) {
        boardPtr = boardIn;
        vector<vector<char>>& board = *boardPtr;
        initContainers();
        for (int row = 0; row < boardsize; ++row) {
            for (int col = 0; col < boardsize; ++col) {
                if (board[row][col] != '.') {
                    rows[row].erase(board[row][col] - '0');
                    cols[col][board[row][col] - '0'] = true;
                    squares[calcsquare(row, col)][board[row][col] - '0'] = true;
                }
            }
        }
        for (int _ = 1; _ <= 5; ++_) {
            // while (checkAll()) {}
            checkAllSingles();
        }
    }
};