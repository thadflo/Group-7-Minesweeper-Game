#include <stdlib.h>
#include <ctime>
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

tile** generateBombs(tile** board, int bombs, int initialX, int initialY) {
    int bombCount = bombs;
    tile** bombBoard = board;
    int minSafeX = initialX == 0 ? 0 : initialX - 1;
    int maxSafeX = initialX == 9 ? 9 : initialX + 1;
    int minSafeY = initialY == 0 ? 0 : initialY - 1;
    int maxSafeY = initialY == 9 ? 9 : initialY + 1;

    while(bombCount > 0){
        int canaditeY = rand() % BOARD_SIZE;
        int canaditeX = rand() % BOARD_SIZE;

        tile canaditeTile = board[canaditeY][canaditeX];
        if (canaditeTile.tileValue != 9 && 
            (canaditeX < minSafeX || canaditeX > maxSafeX || 
            canaditeY < minSafeY || canaditeY > maxSafeY)) {
                bombBoard[canaditeY][canaditeX].tileValue = 9;
                bombCount -= 1;
        }
    }

    return bombBoard;
}

int main() {
    srand(time(nullptr)); //Seed random so board is actually random
    tile** board = generateBlankBoard();
    tile** bombBoard = generateBombs(board, 10, 9, 9);
    printBoard(bombBoard);
    return 0;
}