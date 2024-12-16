#pragma once
#include <string>
#include "board.hpp"

bool ask_game_mode();

void draw_progress_animation();

void draw_title();

void dynamic_menu();

int ask_board_size();

char ask_symbol(const char default_symbol);

std::string ask_name();

void draw_game_board(const Board board, const int cell_size, char player_a_symbol, char player_b_symbol);

std::string ask_coordinates(const std::string player_name, int max_size);