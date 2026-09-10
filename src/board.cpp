#include <stdlib.h>
#include <ctime>
#include <iostream>
#include "board.hpp"
using namespace std;

const int BOARD_SIZE = 10;

void printBoard(Tile** board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            int tileValue = board[i][j].tileValue;
            cout << tileValue<<" ";
        }
        cout << endl;
    }

    return;
}

Tile** generateBlankBoard() {
    Tile** board = new Tile*[BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[i] = new Tile[BOARD_SIZE];
        for (int j = 0; j < BOARD_SIZE; ++j) {
            Tile newTile;
            newTile.tileValue = 0;
            newTile.tileState = COVERED;
            board[i][j] = newTile;
        }
    }
    return board;
}

void markTiles(Tile** board, int bombX, int bombY) {
    Tile& bombTile = board[bombY][bombX];
    bombTile.tileValue = 9;

    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if((bombX + i >= 0) && (bombX + i < BOARD_SIZE)
            && (bombY + j >= 0) && (bombX + j < BOARD_SIZE)) {
                Tile& updateTile = board[bombY + j][bombX + i];
                if(updateTile.tileValue != 9) {
                    updateTile.tileValue += 1;
                }
            }
        }
    }
}

Tile** generateBombs(Tile** board, int bombs, int initialX, int initialY) {
    int bombCount = bombs;
    Tile** bombBoard = board;
    int minSafeX = initialX == 0 ? 0 : initialX - 1;
    int maxSafeX = initialX == 9 ? 9 : initialX + 1;
    int minSafeY = initialY == 0 ? 0 : initialY - 1;
    int maxSafeY = initialY == 9 ? 9 : initialY + 1;

    while(bombCount > 0){
        int canaditeY = rand() % BOARD_SIZE;
        int canaditeX = rand() % BOARD_SIZE;

        Tile canaditeTile = board[canaditeY][canaditeX];
        if (canaditeTile.tileValue != 9 && 
            (canaditeX < minSafeX || canaditeX > maxSafeX || 
            canaditeY < minSafeY || canaditeY > maxSafeY)) {
                markTiles(bombBoard, canaditeX, canaditeY);
                bombCount -= 1;
        }
    }

    return bombBoard;
}

int main() {
    srand(time(nullptr)); //Seed random so board is actually random
    Tile** board = generateBlankBoard();
    Tile** bombBoard = generateBombs(board, 10, 9, 9);
    printBoard(bombBoard);
    return 0;
}
