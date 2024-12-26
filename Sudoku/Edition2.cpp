#include <deque>
#include <iostream>
#include <limits>
#include <ostream>
#include <unordered_map>
using namespace std;


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
        os << i << endl;
    }
    return os;
}

template <typename T>
auto operator<<(ostream& os, pair<T, T> const& p) -> ostream& {
    os << p.first << " " << p.second << endl;
    return os;
}

int const boardsize = 9;
class Solution {
    auto Solve() -> void;

    class impossibleException : public exception {};

    vector<vector<char>>* boardptr;

    vector<unordered_map<uint32_t, bool>> rows;
    vector<vector<bool>> cols;
    vector<vector<bool>> squares;

    deque<pair<uint32_t, uint32_t>> empties;
    deque<pair<uint32_t, uint32_t>> updateOrder;

    auto currentSquare(uint32_t row, uint32_t col) -> vector<bool>& { return squares[((row / 3) * 3) + (col / 3)]; }

    auto initContainers() -> void {
        vector<vector<char>>& board = *boardptr;

        unordered_map<uint32_t, bool> templ;
        templ.reserve(boardsize);
        for (uint32_t i = 1; i <= boardsize; ++i) {
            templ.emplace(i, false);
        }

        rows.resize(boardsize, templ);
        cols.resize(boardsize, vector<bool>(boardsize + 1));
        squares.resize(boardsize, vector<bool>(boardsize + 1));

        for (uint32_t row = 0; row < boardsize; ++row) {
            for (uint32_t col = 0; col < boardsize; ++col) {
                if (board[row][col] == '.') {
                    empties.emplace_back(row, col);
                } else {
                    uint32_t const toErase = board[row][col] - '0';
                    rows[row].erase(toErase);
                    cols[col][toErase] = true;
                    currentSquare(row, col)[toErase] = true;
                }
            }
        }

        for (auto row : rows) {
            for (auto entry : row) {
                cout << entry.first << " ";
            }
            cout << endl;
        }


        // for (auto i : empties) {
        //     cout << i << endl;
        // }
    }

    auto solved() -> bool { return empties.empty(); }

    auto updateCell(uint32_t row, uint32_t col, uint32_t val) -> void {
        (*boardptr)[row][col] = val + '0';
        rows[row].erase(val);
        cols[col][val] = true;
        currentSquare(row, col)[val] = true;
        updateOrder.emplace_front(row, col);
        cout << (*boardptr)[row][col] << " inserted at row " << row << " col " << col << endl;
    }

    auto FillSingleCell(uint32_t row, uint32_t col) -> bool {
        uint32_t possible = 0;
        bool foundPossible = false;
        for (auto const& iter : rows[row]) {
            if (!cols[col][iter.first] and !currentSquare(row, col)[iter.first]) {
                // cout << "row " << row << " col " << col << " possible " << iter.first << endl;
                if (foundPossible) {
                    return false;
                }
                possible = iter.first;
                foundPossible = true;
            }
        }
        if (!foundPossible) {
            cout << "no valid value at row " << row << " col " << col << endl;
            throw impossibleException();
        }
        updateCell(row, col, possible);
        return true;
    }
    auto FillSingles() -> void {
        cout << "Filling Singles..." << endl;
        uint32_t leftToCheck = empties.size();
        while (leftToCheck > 0) {
            pair<uint32_t, uint32_t> const a = empties.front();
            empties.pop_front();
            if (FillSingleCell(a.first, a.second)) {
                leftToCheck = empties.size();
            } else {
                empties.push_back(a);
                --leftToCheck;
            }
        }
    }

    auto findMinPossible() -> pair<uint32_t, uint32_t> {
        uint32_t minSeen = numeric_limits<uint32_t>::max();
        pair<uint32_t, uint32_t> min;
        uint32_t count = 0;
        auto sw = empties.begin();
        for (auto entry = empties.begin(); entry != empties.end(); ++entry) {
            count = 0;
            for (auto val : rows[entry->first]) {
                if (!cols[entry->second][val.first] and !currentSquare(entry->first, entry->second)[val.first]) {
                    ++count;
                }
            }
            if (count < minSeen) {
                sw = entry;
                minSeen = count;
                min = *entry;
                if (minSeen == 2) {
                    break;
                }
            }
        }
        cout << "count: " << count << endl;
        // cout << "row: ";
        // for (auto value : rows[min.first]) {
        //     cout << value.first << ' ';
        // }
        // cout << endl;
        // cout << "col: " << cols[min.second] << endl;
        // cout << "squares: " << currentSquare(min.first, min.second);
        // exit(0);
        swap(*sw, *empties.begin());
        return min;
    }

    void revertCell(pair<uint32_t, uint32_t>& cell) {
        auto const val = (*boardptr)[cell.first][cell.second] - '0';
        rows[cell.first].emplace(val, false);
        cols[cell.second][val] = false;
        currentSquare(cell.first, cell.second)[val] = false;
        (*boardptr)[cell.first][cell.second] = '.';

        cout << "reverting " << endl;
    }

    auto RandAdd() -> void {
        cout << "adding random" << endl;
        pair<uint32_t, uint32_t> const mini = findMinPossible();
        cout << empties.front() << endl;
        empties.pop_front();
        cout << "Pair: " << mini << endl;

        auto currrow = rows[mini.first];

        for (auto val : currrow) {
            if (!cols[mini.second][val.first] and !currentSquare(mini.first, mini.second)[val.first]) {
                try {
                    updateCell(mini.first, mini.second, val.first);
                    Solve();
                    return;
                } catch (impossibleException& e) {
                    cout << "unsuccessful with value " << val.first << " at row " << mini.first << " col "
                         << mini.second << endl;
                    for (; !updateOrder.empty(); updateOrder.pop_front()) {
                        revertCell(updateOrder.front());
                        if (updateOrder.front() == mini) {
                            break;
                        }
                        empties.push_back(updateOrder.front());
                    }
                    cout << updateOrder.size() << endl;
                    updateOrder.pop_front();
                }
            }
        }
        if ((*boardptr)[mini.first][mini.second] == '.') {
            empties.push_back(mini);
            throw impossibleException();
        }
    }

public:
    auto solveSudoku(vector<vector<char>>& board) -> void {
        boardptr = &board;
        initContainers();
        Solve();
    }
};

auto Solution::Solve() -> void {
    cout << "starting solve..." << endl;
    FillSingles();
    if (solved()) {
        cout << "solved!" << endl;
        return;
    }
    RandAdd();
}