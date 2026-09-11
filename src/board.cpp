#include "board.hpp"
#include <cstdint>
#include <cstdlib>

constexpr std::uint8_t min(std::uint8_t a, std::uint8_t b) {
	return a < b ? a : b;
}

constexpr std::uint8_t max(std::uint8_t a, std::uint8_t b) {
	return a > b ? a : b;
}


// Board::Board(std::size_t board_size)
// Creates uninstantiated board


void Board::generate_tile_values(std::uint8_t x, std::uint8_t y) {
	std::uint8_t i = min(x - 1, x), j = min(y - 1, y);
	constexpr std::uint8_t max_value = board_size - 1;
	std::uint8_t fin_i = max(max_value, x + 1), fin_j = max(max_value, y + 1);
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
		std::uint8_t rand_x = rand() % board_size;
		std::uint8_t rand_y = rand() % board_size;
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
