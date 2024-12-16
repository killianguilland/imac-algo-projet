#pragma once

#include <vector>

enum class CellState {
    EMPTY,
    PLAYER_A,
    PLAYER_B
};

struct Board {
    std::vector<CellState> cells;
    int size;

    Board(int board_size);

    int coordinates_to_index(std::string coordinates) const;

    std::string index_to_coordinates(int index) const;

    CellState get_value_from_coordinates(std::string coordinates);

    void set_value_from_coordinates(std::string coordinates, CellState value);

    bool is_full();

    CellState check_if_someone_won();

    void reset();

    void debug_dump();
};