#include "input_handler.hpp"

InputHandler::InputHandler(int board_size) : m_board_size(board_size) {}

std::pair<int, int> InputHandler::get_tile(int button_id) const {
    // Button IDs are assigned left-to-right, top-to-bottom, starting at 1.
    int zero_based_id = button_id - 1;
    int row = zero_based_id / m_board_size;
    int col = zero_based_id % m_board_size;
    return {row, col};
}

void InputHandler::handle_tile_click(int button_id, ClickType type) {
    // convert the UI button ID before notifying game logic about the tile.
    auto [row, col] = get_tile(button_id);
 
    if (type == ClickType::LEFT) {
        // a left click reveals a tile; the callback is optional during setup.
        if (on_reveal_tile) {
            on_reveal_tile(row, col);
        }
    } else {
        // a right click toggles the tile's flag through the game logic layer.
        if (on_flag_tile) {
            on_flag_tile(row, col);
        }
    }
}
 
void InputHandler::handle_start_game(int num_bombs) {
    if (on_start_game) {
        on_start_game(num_bombs);
    }
}
 
void InputHandler::handle_retry() {
    if (on_retry) {
        on_retry();
    }
}
 
void InputHandler::handle_close() {
    if (on_close) {
        on_close();
    }
}