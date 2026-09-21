// for std::uint8_t
#include <cstdint>
constexpr std::uint8_t GRID_SIZE = 10;

class Tile {
	public:
		// Want Covered to be default state
		enum TileState { Covered, Flagged, Uncovered};
		
		std::uint8_t tile_value; //0 for blank, 9 for bomb
		TileState tile_state;
};

class Board {
	private:
		Tile tiles[GRID_SIZE][GRID_SIZE] = {0};
		void update_tile_values(std::uint8_t x, std::uint8_t y);
		void uncover_surrounding(std::uint8_t x, std::uint8_t y);
		bool is_empty(std::uint8_t x, std::uint8_t y);

	public:
		// Board Constructor
		Board() {};
		void initialize(std::uint8_t bomb_count, std::uint8_t x, std::uint8_t y);

		bool is_bomb(std::uint8_t x, std::uint8_t y);
		std::uint8_t get_tile_value(std::uint8_t x, std::uint8_t y) const; 
		Tile::TileState get_state(std::uint8_t x, std::uint8_t y);

		void toggle_flag(std::uint8_t x, std::uint8_t y);
		
		// return true if a bomb was uncovered
		bool uncover(std::uint8_t x, std::uint8_t y);

		//Not sure if neccessary but might need to free Board.tiles 
		~Board() {};
};
