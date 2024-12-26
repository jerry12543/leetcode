#include "Edition4.h"
using namespace std;

auto Solution::initContainers() -> void {
    vector<vector<char>>& board = *boardptr;

    rows.resize(boardsize);
    cols.resize(boardsize);
    squares.resize(boardsize);


    for (uint32_t row = 0; row < boardsize; ++row) {
        for (uint32_t col = 0; col < boardsize; ++col) {
            if (board[row][col] == '.') {
                empties.emplace_back(row, col);
            } else {
                uint32_t const toErase = board[row][col] - '0';
                rows[row][toErase] = true;
                cols[col][toErase] = true;
                currentSquare(row, col)[toErase] = true;
            }
        }
    }
}

auto Solution::updateCell(uint32_t row, uint32_t col, uint32_t val) -> void {
    (*boardptr)[row][col] = val + '0';
    rows[row][val] = true;
    cols[col][val] = true;
    currentSquare(row, col)[val] = true;
    updateOrder.emplace_front(row, col);

    if (verbose) {
        cout << (*boardptr)[row][col] << " inserted at row " << row << " col " << col << endl;
    }
}

void Solution::revertCell(pair<uint32_t, uint32_t>& cell) {
    auto const val = (*boardptr)[cell.first][cell.second] - '0';
    rows[cell.first][val] = false;
    cols[cell.second][val] = false;
    currentSquare(cell.first, cell.second)[val] = false;
    (*boardptr)[cell.first][cell.second] = '.';

    if (verbose) {
        cout << "reverting row " << cell.first << " col " << cell.second << endl;
    }
}

auto Solution::FillSingleCell(uint32_t row, uint32_t col) -> bool {
    uint32_t possible = 0;
    bool foundPossible = false;

    for (uint32_t val = 1; val <= boardsize; ++val) {
        if (!rows[row][val] and !cols[col][val] and !currentSquare(row, col)[val]) {
            if (foundPossible) {
                return false;
            }
            possible = val;
            foundPossible = true;
        }
    }
    if (!foundPossible) {
        if (verbose) {
            cout << "no valid value at row " << row << " col " << col << endl;
        }
        empties.emplace_back(row, col);
        throw impossibleException();
    }
    updateCell(row, col, possible);
    return true;
}

auto Solution::FillSingles() -> void {
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

auto Solution::findMinPossible() -> pair<uint32_t, uint32_t> {
    uint32_t minSeen = numeric_limits<uint32_t>::max();
    pair<uint32_t, uint32_t> min;
    uint32_t count = 0;
    auto sw = empties.begin();
    for (auto entry = empties.begin(); entry != empties.end(); ++entry) {
        count = 0;
        for (uint32_t val = 1; val <= boardsize; ++val) {
            if (!rows[entry->first][val] and !cols[entry->second][val]
                and !currentSquare(entry->first, entry->second)[val]) {
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

    if (verbose) {
        cout << "Min Possible: " << count << " at row " << min.first << " col " << min.second << endl;
    }
    swap(*sw, *empties.begin());
    return min;
}

auto Solution::RandAdd() -> void {
    if (verbose) {
        cout << "adding random" << endl;
    }

    pair<uint32_t, uint32_t> const mini = findMinPossible();
    empties.pop_front();

    for (uint32_t val = 1; val <= boardsize; ++val) {
        if (!rows[mini.first][val] and !cols[mini.second][val] and !currentSquare(mini.first, mini.second)[val]) {
            try {
                updateCell(mini.first, mini.second, val);
                return Solve();
            } catch (impossibleException& e) {
                if (verbose) {
                    cout << "unsuccessful with value " << val << " at row " << mini.first << " col " << mini.second
                         << endl;
                }
                for (; !updateOrder.empty(); updateOrder.pop_front()) {
                    revertCell(updateOrder.front());
                    if (updateOrder.front() == mini) {
                        break;
                    }
                    empties.push_back(updateOrder.front());
                }
                updateOrder.pop_front();
            }
        }
    }
    if ((*boardptr)[mini.first][mini.second] == '.') {
        empties.push_back(mini);
        throw impossibleException();
    }
}

auto Solution::solveSudoku(vector<vector<char>>& board) -> void {
    boardptr = &board;
    initContainers();
    Solve();
}

auto Solution::Solve() -> void {
    cout << "starting solve..." << endl;
    FillSingles();
    if (solved()) {
        cout << "solved!" << endl;
        return;
    }
    RandAdd();
}