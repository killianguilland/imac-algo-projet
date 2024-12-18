#include <settings.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "ui.hpp"
#include "player.hpp"
#include "lib/random.hpp"

Player::Player(const std::string& name, char symbol) {
    this->name = name;
    this->symbol = symbol;
    this->is_ai = false;
}

std::string Player::get_move(const Board& board) const {
    return ask_coordinates(name, board.size);
}

AIPlayer::AIPlayer(const std::string& name, char symbol, DifficultyChoice difficulty) {
    this->name = name;
    this->symbol = symbol;
    this->is_ai = true;
    this->difficulty = difficulty;
}

std::string AIPlayer::get_move(const Board& board) const {
    std::string coordinates {};

    switch(difficulty)
    {
        case DifficultyChoice::EASY:
            {
                std::vector<int> empty_cells {};
                
                for (int i = 0; i < board.cells.size(); i++)
                {
                    if(board.cells[i] == CellState::EMPTY) {
                        empty_cells.push_back(i);
                    }
                }

                int random_index = random_int(0, empty_cells.size() - 1);

                coordinates = board.index_to_coordinates(empty_cells[random_index]);
                break;
            }
        
        case DifficultyChoice::HARD:
            {
                Board board_copy = board;
                std::vector<std::string> winning_moves {};
                std::vector<std::string> blocking_moves {};
                std::vector<std::string> random_moves {};

                for (int i = 0; i < board.cells.size(); i++)
                {
                    if(board.cells[i] == CellState::EMPTY) {
                        std::string current_coordinates = board.index_to_coordinates(i);
                        board_copy.set_value_from_coordinates(current_coordinates, CellState::PLAYER_B);
                        CellState winner = board_copy.check_if_someone_won();
                        board_copy.set_value_from_coordinates(current_coordinates, CellState::EMPTY);

                        std::cout << "Current coordinates : " << current_coordinates << std::endl;
                        if(winner == CellState::PLAYER_B) {
                            std::cout << "AI is winning" << std::endl;
                            winning_moves.push_back(current_coordinates);
                            continue;
                        }

                        board_copy.set_value_from_coordinates(current_coordinates, CellState::PLAYER_A);
                        winner = board_copy.check_if_someone_won();
                        board_copy.set_value_from_coordinates(current_coordinates, CellState::EMPTY);
                        
                        if(winner == CellState::PLAYER_A) {
                            std::cout << "Player is winning" << std::endl;
                            blocking_moves.push_back(current_coordinates);
                            continue;
                        }
                        
                        std::cout << "No one is winning" << std::endl;
                        random_moves.push_back(current_coordinates);
                    }
                }

                if(winning_moves.size() > 0) {
                    std::cout << "AI is winning" << std::endl;
                    coordinates = winning_moves.at(0);
                } else if(blocking_moves.size() > 0) {
                    std::cout << "AI is blocking" << std::endl;
                    coordinates = blocking_moves.at(0);
                } else {
                    std::cout << "AI is playing randomly" << std::endl;
                    coordinates = random_moves[random_int(0, random_moves.size() - 1)];
                }
                break;
            }
    }

    return coordinates;
}

Player create_player(const char default_symbol) {
    std::string name {ask_name()};
    char symbol {ask_symbol(default_symbol)};
    return Player{name, symbol};
}

AIPlayer create_ai_player(const char default_symbol, DifficultyChoice difficulty) {
    return AIPlayer{"AI", default_symbol, difficulty};
}