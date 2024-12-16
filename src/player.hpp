#pragma once
#include <string>
#include "board.hpp"

struct BasePlayer {
    std::string name;
    char symbol;
    bool is_ai;

    virtual std::string get_move(const Board& board) const = 0;
};

struct Player : BasePlayer {
    Player(const std::string& name, char symbol);
    std::string get_move(const Board &board) const override;
};

struct AIPlayer : BasePlayer {
    AIPlayer(const std::string& name, char symbol);
    std::string get_move(const Board &board) const override;
};

Player create_player(const char player_letter);
AIPlayer create_ai_player(const char player_letter);