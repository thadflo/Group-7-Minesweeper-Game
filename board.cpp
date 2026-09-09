#include <stdlib.h>
#include <iostream>
#include "tile.h"
using namespace std;

const int BOARD_SIZE = 10;

void printBoard(tile** board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            int tileValue = board[i][j].tileValue;
            cout << tileValue<<" ";
        }
        cout << endl;
    }

    return;
}

tile** generateBlankBoard() {
    tile** board = new tile*[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[i] = new tile[BOARD_SIZE];
        for (int j = 0; j < BOARD_SIZE; ++j) {
            tile newTile;
            newTile.tileValue = 0;
            newTile.tileState = COVERED;
            board[i][j] = newTile;
        }
    }
    return board;
}

int main() {
    tile** board = generateBlankBoard();
    printBoard(board);
    return 0;
}