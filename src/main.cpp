#include <iostream>
#include "settings.hpp"
#include "ui.hpp"
#include "player.hpp"
#include "board.hpp"

int main() {
    init_raylib();

    draw_title();

    int board_size {ask_board_size()};

    draw_title();

    bool ai_mode {ask_game_mode()};

    draw_title();

    Player player_a {create_player(PLAYER_A_SYMBOL)};

    draw_title();

    BasePlayer* player_b;

    if (ai_mode) {
        DifficultyChoice difficulty {ask_difficulty()};
        player_b = new AIPlayer{create_ai_player(PLAYER_B_SYMBOL, difficulty)};
    } else {
        player_b = new Player{create_player(PLAYER_B_SYMBOL)};
    }

    Board board{board_size};

    char current_player_index = 0;

    while (true) {
        draw_title();

        BasePlayer& current_player = current_player_index ? *player_b : player_a;

        // board.debug_dump();

        draw_game_board(board, CELL_SIZE, player_a.symbol, player_b->symbol);

        std::string coordinates {};

        if(current_player.is_ai) {
            draw_progress_animation();
        }

        coordinates = current_player.get_move(board);

        if(current_player.is_ai) {
            announce_ai_move(coordinates);
        }

        CellState cell_state = board.get_value_from_coordinates(coordinates);

        if (cell_state != CellState::EMPTY) {
            std::cout << "Cette case est déjà prise !" << std::endl;
            continue;
        }

        board.set_value_from_coordinates(coordinates, current_player_index ? CellState::PLAYER_B : CellState::PLAYER_A);

        CellState winner = board.check_if_someone_won();

        if (winner != CellState::EMPTY) {
            draw_title();
            draw_game_board(board, CELL_SIZE, player_a.symbol, player_b->symbol);
            std::cout << "Le joueur " << (current_player_index ? player_b->name : player_a.name) << " a gagné !" << std::endl;
            break;
        }

        if (board.is_full()) {
            draw_title();
            draw_game_board(board, CELL_SIZE, player_a.symbol, player_b->symbol);
            std::cout << "Match nul !" << std::endl;
            break;
        }

        current_player_index = current_player_index ? 0 : 1;
    }

    return 0;
}