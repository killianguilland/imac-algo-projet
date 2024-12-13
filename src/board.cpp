#include <vector>
#include "board.hpp"
#include <iostream>

Board::Board(int board_size) {
    size = board_size;
    cells.resize(size * size, CellState::EMPTY);
}

int Board::coordinates_to_index(std::string coordinates) {
    char a = coordinates[0] - 65;
    int y = coordinates[1] - 49;
    return a + y * size;
}

CellState Board::get_value_from_coordinates(std::string coordinates) {
    return cells[coordinates_to_index(coordinates)];
}

void Board::set_value_from_coordinates(std::string coordinates, CellState value) {
    std::cout << coordinates << std::endl;
    std::cout << coordinates_to_index(coordinates) << std::endl;
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
    for (int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++) {
            CellState cell = cells[i * size + j];
            if (cell == CellState::EMPTY) {
                continue;
            }

            // Check horizontal
            if (j + 2 < size && cell == cells[i * size + j + 1] && cell == cells[i * size + j + 2]) {
                return cell;
            }

            // Check vertical
            if (i + 2 < size && cell == cells[(i + 1) * size + j] && cell == cells[(i + 2) * size + j]) {
                return cell;
            }

            // Check diagonal
            if (i + 2 < size && j + 2 < size && cell == cells[(i + 1) * size + j + 1] && cell == cells[(i + 2) * size + j + 2]) {
                return cell;
            }

            if (i + 2 < size && j - 2 >= 0 && cell == cells[(i + 1) * size + j - 1] && cell == cells[(i + 2) * size + j - 2]) {
                return cell;
            }
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