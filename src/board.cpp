#include "board.hpp"
#include <cstdint>
#include <cstdlib>

constexpr std::uint8_t min(std::uint8_t a, std::uint8_t b) {
	return a < b ? a : b;
}

constexpr bool in_3_by_3_range(std::uint8_t x, std::uint8_t y, std::uint8_t new_x, std::uint8_t new_y) {
	bool below = new_y <= min(y + 1, board_size), above = new_y >= min(y - 1, y);
	bool left = new_x <= min(x + 1, board_size), right = new_x >= min(x - 1, x);
	return (below && above) && (left && right);
}


// Board::generate_tile_values
// Used by Board::Iniitialize
// Adds the +1 to all surrounding non-bomb tiles
void Board::update_tile_values(std::uint8_t x, std::uint8_t y) {
	// uint8_t is unsigned so if x/y = 0 x-1 will be bigger than x :)
	std::uint8_t i = min(y - 1, y), initial_j = min(x - 1, x);
	constexpr std::uint8_t max_value = board_size - 1;
	std::uint8_t fin_i = min(max_value, y + 1), fin_j = min(max_value, x + 1);
	for(;i <= fin_i; i++) {
		for(int j = initial_j;j <= fin_j;j++) {
			if(i == x && j == y)
				continue;
			if(this->tiles[i][j].tile_value != 9)
				this->tiles[i][j].tile_value++;
		}
	}
}

// Board::initialize
// Places bombs randomly 
void Board::initialize(std::uint8_t nbombs, std::uint8_t x, std::uint8_t y) {
	while(nbombs > 0) {
		std::uint8_t rand_x = rand() % board_size;
		std::uint8_t rand_y = rand() % board_size;
		if(in_3_by_3_range(x, y, rand_x, rand_y))
			continue;
		Tile tile = this->tiles[rand_y][rand_x];
		if(tile.tile_value == 9)
			continue;
		this->tiles[rand_y][rand_x].tile_value = 9;
		this->update_tile_values(rand_x, rand_y);
		nbombs--;
	}
}
