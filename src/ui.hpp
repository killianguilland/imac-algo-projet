#pragma once
#include <string>
#include "board.hpp"
#include "player.hpp"

bool ask_game_mode();

void draw_progress_animation();

void draw_title();

void dynamic_menu();

int ask_board_size();

DifficultyChoice ask_difficulty();

char ask_symbol(const char default_symbol);

std::string ask_name();

void draw_game_board(const Board board, const int cell_size, char player_a_symbol, char player_b_symbol);

void announce_ai_move(const std::string coordinates);

std::string ask_coordinates(const std::string player_name, int max_size);