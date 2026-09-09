#include <stdlib.h>
#include "tile.h"

const int BOARD_SIZE = 10;

tile** generateTestBoard() {
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