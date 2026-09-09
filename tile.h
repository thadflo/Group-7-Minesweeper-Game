enum TileState {
    FLAGGED,
    COVERED,
    UNCOVERED
};

class tile
{
    public:
        int tileValue; //0 for blank, 9 for bomb
        TileState tileState;
};