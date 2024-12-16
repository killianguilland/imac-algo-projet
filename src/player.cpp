#include <settings.hpp>
#include <string>
#include <vector>
#include "ui.hpp"
#include "player.hpp"
#include "lib/random.hpp"
// #include <iostream>
// #include "terminal_ctrl.hpp"

Player::Player(const std::string& name, char symbol) {
    this->name = name;
    this->symbol = symbol;
    this->is_ai = false;
}

std::string Player::get_move(const Board& board) const {
    return ask_coordinates(name, board.size);
}

AIPlayer::AIPlayer(const std::string& name, char symbol) {
    this->name = name;
    this->symbol = symbol;
    this->is_ai = true;
}

std::string AIPlayer::get_move(const Board& board) const {
    std::vector<int> empty_cells {};
    
    for (int i = 0; i < board.cells.size(); i++)
    {
        if(board.cells[i] == CellState::EMPTY) {
            empty_cells.push_back(i);
            //std::cout << i << std::endl;
        }
    }

    int random_index = random_int(0, empty_cells.size() - 1);

    std::string coordinates {board.index_to_coordinates(empty_cells[random_index])};

    // std::cout << "L'IA joue en " << coordinates << std::endl;

    // terminal_ctrl::sleep(1000);

    return coordinates;
}

Player create_player(const char default_symbol) {
    std::string name {ask_name()};
    char symbol {ask_symbol(default_symbol)};
    return Player{name, symbol};
}

AIPlayer create_ai_player(const char default_symbol) {
    return AIPlayer{"AI", default_symbol};
}