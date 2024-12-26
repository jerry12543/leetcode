#include <deque>
#include <iostream>
#include <limits>
#include <ostream>
#include <unordered_map>

template <typename T>
auto operator<<(std::ostream& os, std::vector<T> const& vec) -> std::ostream& {
    for (T const i : vec) {
        os << i << " ";
    }
    return os;
}
template <typename T>
auto operator<<(std::ostream& os, std::vector<std::vector<T>> const& vec) -> std::ostream& {
    for (auto const& i : vec) {
        os << i << std::endl;
    }
    return os;
}

template <typename T>
auto operator<<(std::ostream& os, std::pair<T, T> const& p) -> std::ostream& {
    os << p.first << " " << p.second << std::endl;
    return os;
}


class Solution {
    class impossibleException : public std::exception {};
    static uint32_t const boardsize = 9;

    bool verbose = false;
    std::vector<std::vector<char>>* boardptr;

    std::vector<std::bitset<boardsize + 1>> rows, cols, squares;
    std::deque<std::pair<uint32_t, uint32_t>> empties, updateOrder;


    // Returns the box the given cell resides in
    [[nodiscard]] auto currentSquare(uint32_t row, uint32_t col) -> std::bitset<boardsize + 1>& {
        return squares[((row / 3) * 3) + (col / 3)];
    }
    // Initializes class variables
    auto initContainers() -> void;
    // Returns true if the board is solved
    [[nodiscard]] auto solved() -> bool { return (empties.empty()); }
    // Updates the given cell with the value, adds cell to front of updateOrder
    // Removes the value from possible choices for the row, col, and square
    auto updateCell(uint32_t row, uint32_t col, uint32_t val) -> void;
    // Reverts cell back to '.'
    // Adds value back to possible choices for row, col, and square
    void revertCell(std::pair<uint32_t, uint32_t>& cell);
    // Fills the cell with a value if that is the only possible value
    // Returns true if the cell was filled
    auto FillSingleCell(uint32_t row, uint32_t col) -> bool;
    // Fills all cells with only one possible choice
    auto FillSingles() -> void;
    // Finds the cell that has the smallest number of possible values
    auto findMinPossible() -> std::pair<uint32_t, uint32_t>;
    // Chooses a square and goes through all possible valid values (up to this point) until a correct one is found
    auto RandAdd() -> void;
    // Solves the board pointed to by boardptr
    auto Solve() -> void;

public:
    // Solves the Sudoku board
    auto solveSudoku(std::vector<std::vector<char>>& board) -> void;
};