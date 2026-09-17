#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <functional>
#include <utility>

// What kind of click happened on a tile button
enum class ClickType {
    LEFT,   // reveal the tile
    RIGHT   // flag / unflag the tile
};

// InputHandler owns no game state itself. It just converts raw UI
// events into semantic calls, and fires
// callbacks that Board Manager/Game Logic / UI Manager attach to.
class InputHandler {
    public:
        // board_size is the width/height of the square board
        // needed to turn a flat button id into (row, col)
        explicit InputHandler(int board_size);

        // Converts a 1-based flat button id into zero-based (row, col).
        std::pair<int, int> get_tile(int button_id) const;

        // Call these from UIManager's signal handlers
        void handle_tile_click(int button_id, ClickType type);
        void handle_start_game(int num_bombs);
        void handle_retry();
        void handle_close();

        // Hooks for other modules to attach behavior. Left unset ==
        // no-op, so this compiles and runs standalone before anyone
        // else's code exists.
        std::function<void(int row, int col)> on_reveal_tile;
        std::function<void(int row, int col)> on_flag_tile;
        std::function<void(int num_bombs)> on_start_game;
        std::function<void()> on_retry;
        std::function<void()> on_close;

    private:
        int m_board_size;
};

#endif // INPUT_HANDLER_H