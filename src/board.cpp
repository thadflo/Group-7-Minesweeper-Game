#include "board.hpp"
#include <cstdint>
#include <cstdlib>

using namespace std;

constexpr uint8_t min(uint8_t a, uint8_t b) {
	return a < b ? a : b;
}
constexpr bool in_3_by_3_range(uint8_t x, uint8_t y, uint8_t new_x, uint8_t new_y) {
	bool below = new_y <= min(y + 1, board_size), above = new_y >= min(y - 1, y);
	bool left = new_x <= min(x + 1, board_size), right = new_x >= min(x - 1, x);
	return (below && above) && (left && right);
}

// Board::generate_tile_values
// Used by Board::Iniitialize
// Adds the +1 to all surrounding non-bomb tiles
void Board::update_tile_values(uint8_t x, uint8_t y) {
	// uint8_t is unsigned so if x/y = 0 x-1 will be bigger than x :)
	uint8_t cur_y = min(y - 1, y), init_x = min(x - 1, x);
	constexpr uint8_t max_value = board_size - 1;
	uint8_t fin_y = min(max_value, y + 1), fin_x = min(max_value, x + 1);
	for(;cur_y <= fin_y; cur_y++) {
		for(uint8_t cur_x = init_x; cur_x <= fin_x; cur_x++) {
			if(cur_x == x && cur_y == y)
				continue;
			if(this->tiles[cur_y][cur_x].tile_value != 9)
				this->tiles[cur_y][cur_x].tile_value++;
		}
	}
}

// Board::initialize
// Places bombs randomly and reset the board to a default state
void Board::initialize(uint8_t bomb_count, uint8_t x, uint8_t y) {
	for (int row = 0; row < board_size; ++row) {
		for (int col = 0; col < board_size; ++col) {
			this->tiles[row][col].tile_value = 0;
			this->tiles[row][col].tile_state = Tile::TileState::Covered;
		}
	}

	while (bomb_count > 0) {
		uint8_t rand_x = rand() % board_size;
		uint8_t rand_y = rand() % board_size;
		if (in_3_by_3_range(x, y, rand_x, rand_y))
			continue;
		if (this->tiles[rand_y][rand_x].tile_value == 9)
			continue;
		this->tiles[rand_y][rand_x].tile_value = 9;
		this->update_tile_values(rand_x, rand_y);
		bomb_count--;
	}
}

// Board::is_bomb, returns true if a tile is a bomb
// It is the job of the function caller to ensure input is within the range
bool Board::is_bomb(uint8_t x, uint8_t y) {
	return this->tiles[y][x].tile_value == 9;
}

std::uint8_t Board::get_tile_value(uint8_t x, uint8_t y) const {
	return this->tiles[y][x].tile_value;
}

// Board::get_state returns the state of the tile
// It is the job of the function caller to ensure input is within the range
Tile::TileState Board::get_state(uint8_t x, uint8_t y) {
	return this->tiles[y][x].tile_state;
}

// Board::uncover_surrounding
// a recursive function that uncovers indeced around a state
void Board::uncover_surrounding(uint8_t x, uint8_t y) {
	const uint8_t start_y = min(y - 1, y);
	const uint8_t end_y = min(board_size - 1, y + 1);
	const uint8_t start_x = min(x - 1, x);
	const uint8_t end_x = min(board_size - 1, x + 1);

	for (uint8_t cur_y = start_y; cur_y <= end_y; ++cur_y) {
		for (uint8_t cur_x = start_x; cur_x <= end_x; ++cur_x) {
			if (cur_x == x && cur_y == y)
				continue;
			if (get_state(cur_x, cur_y) == Tile::TileState::Covered && !is_bomb(cur_x, cur_y)) {
				this->tiles[cur_y][cur_x].tile_state = Tile::TileState::Uncovered;
				if (is_empty(cur_x, cur_y))
					uncover_surrounding(cur_x, cur_y);
			}
		}
	}
}

// Board::is_empty
// Toggle from tilestate Flagged to Covered & back
void Board::toggle_flag(std::uint8_t x, std::uint8_t y) {
	Tile::TileState state = get_state(x, y);
	if(state == Tile::TileState::Covered){
		this->tiles[y][x].tile_state = Tile::TileState::Flagged;
	} else if (state == Tile::TileState::Flagged) {
		this->tiles[y][x].tile_state = Tile::TileState::Covered;
	}
}

// Board::is_empty
// used by Board::uncover & Board::uncover_surrounding to determine if recursion is required
bool Board::is_empty(uint8_t x, uint8_t y) {
	return this->tiles[y][x].tile_value == 0;
}

// Board::uncover
// uncovers the requested index, returns true if it's a bomb
bool Board::uncover(uint8_t x, uint8_t y) {
	if (this->tiles[y][x].tile_state == Tile::TileState::Flagged ||
		this->tiles[y][x].tile_state == Tile::TileState::Uncovered) {
		return false;
	}

	this->tiles[y][x].tile_state = Tile::TileState::Uncovered;
	if (!is_bomb(x, y)) {
		if (is_empty(x, y))
			uncover_surrounding(x, y);
		return false;
	}
	return true;
}
