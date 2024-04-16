#include "Board.h"
#include <iostream>

Board::Board() : cells(10, vector<int>(10, 0)) {
    // Initialize the board with empty cells
}

void Board::displayBoard() {
    for (auto &&row : cells) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}
