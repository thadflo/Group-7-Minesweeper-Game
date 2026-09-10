//for std::size_t
#include <cstddef>
#include <stdlib.h>

const int BOARD_SIZE = 10;

enum TileState {
    FLAGGED,
    COVERED,
    UNCOVERED
};

class Tile {
    public:
        int tile_value; //0 for blank, 9 for bomb
        TileState tile_state;
};

class Board {
	private:
		Tile** tiles;
	public:
		// Board Constructor
		Board(std::size_t board_size, int bombs, int initial_y, int initial_x) {

			// Generate a blank board
			Tile** board_tiles = new Tile*[BOARD_SIZE];
			for (int i = 0; i < BOARD_SIZE; ++i) {
				board_tiles[i] = new Tile[BOARD_SIZE];
				for (int j = 0; j < BOARD_SIZE; ++j) {
					Tile new_tile;
					new_tile.tile_value = 0;
					new_tile.tile_state = COVERED;
					board_tiles[i][j] = new_tile;
				}
			}

			//Fill board with bombs and numbers
			int bombCount = bombs;
			Tile** game_board_tiles = board_tiles;
			int min_safe_x = initial_x == 0 ? 0 : initial_x - 1;
			int max_safe_x = initial_x == 9 ? 9 : initial_x + 1;
			int min_safe_y = initial_y == 0 ? 0 : initial_y - 1;
			int max_safe_y = initial_y == 9 ? 9 : initial_y + 1;

			while(bombCount > 0){
				int canaditeY = rand() % BOARD_SIZE;
				int canaditeX = rand() % BOARD_SIZE;

				Tile canaditeTile = game_board_tiles[canaditeY][canaditeX];
				if (canaditeTile.tile_value != 9 && 
					(canaditeX < min_safe_x || canaditeX > max_safe_x || 
					canaditeY < min_safe_y || canaditeY > max_safe_y)) {
						mark_tiles(game_board_tiles, canaditeX, canaditeY);
						bombCount -= 1;
				}
			}

			tiles = board_tiles;

			//
		};

		void mark_tiles(Tile** board_tiles, int bombX, int bombY) {
			Tile& bomb_tile = board_tiles[bombY][bombX];
			bomb_tile.tile_value = 9;

			for(int i = -1; i <= 1; i++) {
				for(int j = -1; j <= 1; j++) {
					if((bombX + i >= 0) && (bombX + i < BOARD_SIZE)
					&& (bombY + j >= 0) && (bombX + j < BOARD_SIZE)) {
						Tile& update_tile = board_tiles[bombY + j][bombX + i];
						if(update_tile.tile_value != 9) {
							update_tile.tile_value += 1;
						}
					}
				}
			}
		}

		//Not sure if neccessary but might need to free Board.tiles 
		~Board();
};
