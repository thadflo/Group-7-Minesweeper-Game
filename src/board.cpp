/*
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include "board.hpp"
using namespace std;

const int BOARD_SIZE = 10;

void print_board(Board board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            int tileValue = board[i][j].tile_value;
            cout << tileValue<<" ";
        }
        cout << endl;
    }

    return;
}


void mark_tiles(Board board, int bombX, int bombY) {
    Tile& bomb_tile = board.tiles[bombY][bombX];
    bomb_tile.tile_value = 9;

    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            if((bombX + i >= 0) && (bombX + i < BOARD_SIZE)
            && (bombY + j >= 0) && (bombX + j < BOARD_SIZE)) {
                Tile& update_tile = board[bombY + j][bombX + i];
                if(update_tile.tile_value != 9) {
                    update_tile.tile_value += 1;
                }
            }
        }
    }
}

Board generate_game_board(Tile** board_tiles, int bombs, int initialX, int initialY) {
    int bombCount = bombs;
    Tile** game_board_tiles = board_tiles;
    int minSafeX = initialX == 0 ? 0 : initialX - 1;
    int maxSafeX = initialX == 9 ? 9 : initialX + 1;
    int minSafeY = initialY == 0 ? 0 : initialY - 1;
    int maxSafeY = initialY == 9 ? 9 : initialY + 1;

    while(bombCount > 0){
        int canaditeY = rand() % BOARD_SIZE;
        int canaditeX = rand() % BOARD_SIZE;

        Tile canaditeTile = game_board_tiles[canaditeY][canaditeX];
        if (canaditeTile.tile_value != 9 && 
            (canaditeX < minSafeX || canaditeX > maxSafeX || 
            canaditeY < minSafeY || canaditeY > maxSafeY)) {
                mark_tiles(game_board_tiles, canaditeX, canaditeY);
                bombCount -= 1;
        }
    }

    return game_board;
}

int main() {
    srand(time(nullptr)); //Seed random so board is actually random
    Board game_board = generate_game_board(generate_blank_board(), 10, 9, 9);
    print_board(game_board);
    return 0;
}
*/