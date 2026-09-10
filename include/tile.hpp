enum TileState {
    FLAGGED,
    COVERED,
    UNCOVERED
};

class Tile
{
    public:
        int tileValue; //0 for blank, 9 for bomb
        TileState tileState;
};
