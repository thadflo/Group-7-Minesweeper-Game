//for std::size_t
#include <cstddef>

enum TileState {
    FLAGGED,
    COVERED,
    UNCOVERED
};

class Tile {
    public:
        int tileValue; //0 for blank, 9 for bomb
        TileState tileState;
};

class Board {
	private:
		Tile** tiles;
	public:
		//Move generate board code to this function
		Board(std::size_t board_size);
		//Not sure if neccessary but might need to free Board.tiles 
		~Board();
};
