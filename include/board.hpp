// for std::uint8_t
#include <cstdint>
constexpr std::uint8_t board_size = 10;

class Tile {
	public:
		// Want Covered to be default state
		enum TileState { Covered, Flagged, Uncovered};
		
		std::uint8_t tile_value; //0 for blank, 9 for bomb
		TileState tile_state;
};

class Board {
	private:
		Tile tiles[board_size][board_size] = {0};
		void generate_tile_values(std::uint8_t x, std::uint8_t y);

	public:
		// Board Constructor
		Board() {};
		void initialize(std::uint8_t nbombs, std::uint8_t x, std::uint8_t y);
		//Not sure if neccessary but might need to free Board.tiles 
		~Board() {};
};
