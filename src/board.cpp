#include <vector>
#include "board.hpp"
#include <iostream>

Board::Board(int board_size) {
    size = board_size;
    cells.resize(size * size, CellState::EMPTY);
}

int Board::coordinates_to_index(std::string coordinates) const {
    char a = coordinates[0] - 65;
    int y = coordinates[1] - 49;
    return a + y * size;
}

std::string Board::index_to_coordinates(int index) const {
    char a = index % size + 65;
    int y = index / size + 1;
    return std::string(1, a) + std::to_string(y);
}

CellState Board::get_value_from_coordinates(std::string coordinates) {
    return cells[coordinates_to_index(coordinates)];
}

void Board::set_value_from_coordinates(std::string coordinates, CellState value) {
    cells[coordinates_to_index(coordinates)] = value;
}

bool Board::is_full() {
    for (CellState cell : cells) {
        if (cell == CellState::EMPTY) {
            return false;
        }
    }
    return true;
}

CellState Board::check_if_someone_won() {

    // Check rows
    for (int i = 0; i < size; i++) {
        CellState first_cell = cells[i * size];
        if (first_cell == CellState::EMPTY) {
            continue;
        }
        bool is_winning_row = true;
        for (int j = 1; j < size; j++) {
            if (cells[i * size + j] != first_cell) {
                is_winning_row = false;
                break;
            }
        }
        if (is_winning_row) {
            return first_cell;
        }
    }

    // Check columns
    for (int i = 0; i < size; i++) {
        CellState first_cell = cells[i];
        if (first_cell == CellState::EMPTY) {
            continue;
        }
        bool is_winning_column = true;
        for (int j = 1; j < size; j++) {
            if (cells[j * size + i] != first_cell) {
                is_winning_column = false;
                break;
            }
        }
        if (is_winning_column) {
            return first_cell;
        }
    }

    // Check diagonals
    CellState first_cell = cells[0];
    if (first_cell != CellState::EMPTY) {
        bool is_winning_diagonal = true;
        for (int i = 1; i < size; i++) {
            if (cells[i * size + i] != first_cell) {
                is_winning_diagonal = false;
                break;
            }
        }
        if (is_winning_diagonal) {
            return first_cell;
        }
    }

    first_cell = cells[size - 1];
    if (first_cell != CellState::EMPTY) {
        bool is_winning_diagonal = true;
        for (int i = 1; i < size; i++) {
            if (cells[i * size + size - 1 - i] != first_cell) {
                is_winning_diagonal = false;
                break;
            }
        }
        if (is_winning_diagonal) {
            return first_cell;
        }
    }
    
    return CellState::EMPTY;
}

void Board::reset() {
    for (CellState &cell : cells) {
        cell = CellState::EMPTY;
    }
}

void Board::debug_dump() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            CellState cell = cells[i * size + j];
            if (cell == CellState::EMPTY) {
                std::cout << "? ";
            } else if (cell == CellState::PLAYER_A) {
                std::cout << "X ";
            } else {
                std::cout << "O ";
            }
        }
        std::cout << std::endl;
    }
}