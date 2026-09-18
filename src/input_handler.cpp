#include "input_handler.hpp"

InputHandler::InputHandler(int board_size) : m_board_size(board_size) {}

std::pair<int, int> InputHandler::get_tile(int button_id) const {
    // Button IDs are assigned left-to-right, top-to-bottom, starting at 1.
    int zero_based_id = button_id - 1;
    int row = zero_based_id / m_board_size;
    int col = zero_based_id % m_board_size;
    return {row, col};
}

std::vector<TileChange> InputHandler::handle_tile_click(int button_id, ClickType type) {
    // convert the UI button ID before notifying game logic about the tile.
    auto [row, col] = get_tile(button_id);
    if (type == ClickType::LEFT) {
        if (on_reveal_tile) {
            return on_reveal_tile(row, col);
        }
    } else {
        if (on_flag_tile) {
            return on_flag_tile(row, col);
        }
    }

    return {};
}
