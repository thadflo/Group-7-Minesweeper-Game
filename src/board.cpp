#include "board.hpp"
#include <cstdint>
#include <cstdlib>

#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b

// Board::Board(std::size_t board_size)
// Creates uninstantiated board


void Board::generate_tile_values(std::uint8_t x, std::uint8_t y) {
	std::uint8_t i = min(x - 1, x), j = min(y - 1, y);
	constexpr std::uint8_t max_value = BOARD_SIZE - 1;
	std::uint8_t fin_i = max(x + 1, max_value), fin_j = max(y + 1, max_value);
	for(;i <= fin_i; i++) {
		for(;j <= fin_j;j++) {
			if(i == x && j == y)
				continue;
			if(this->tiles[i][j].tile_value == 9)
				this->tiles[x][y].tile_value++;
		}
	}
}



void Board::initialize(std::uint8_t nbombs, std::uint8_t x, std::uint8_t y) {
	while(nbombs > 0) {
		std::uint8_t rand_x = rand() % BOARD_SIZE;
		std::uint8_t rand_y = rand() % BOARD_SIZE;
		if(rand_x == x && rand_y == y)
			continue;
		Tile tile = this->tiles[rand_x][rand_y];
		if(tile.tile_value == 9)
			continue;
		this->tiles[rand_x][rand_y].tile_value = 9;
		this->generate_tile_values(rand_x, rand_y);
		nbombs--;
	}
}
