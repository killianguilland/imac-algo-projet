#include <settings.hpp>
#include <iostream>
#include "terminal_ctrl.hpp"
#include "player.hpp"
#include "board.hpp"

// ============
// PLAYER INPUT
// ============

int ask_board_size() {
    std::cout << "Quelle taille doit faire le plateau ? (par défaut: " << BOARD_SIZE << ")" << std::endl;
    std::cout << "➤ ";

    int board_size {BOARD_SIZE};

    // Verify input
    while (true) {
        std::string input {};
        std::getline(std::cin, input);
        if (input.empty()) {
            break;
        } else {
            try {
                board_size = std::stoi(input);
                if (board_size < 3) {
                    std::cout << "La taille du plateau doit être supérieure ou égale à 3" << std::endl;
                    std::cout << "➤ ";
                } else {
                    break;
                }
            } catch (std::invalid_argument) {
                std::cout << "Entre un nombre valide stp" << std::endl;
                std::cout << "➤ ";
            }
        }
    }

    std::cout << std::endl;

    return board_size;
}

char ask_symbol(const char default_symbol) {
    std::cout << "Choisis ton symbole (par défaut = " << default_symbol << ") :" << std::endl;
    std::cout << "➤ ";

    char symbol {};

    // Verify input
    while (true) {
        std::string input {};
        std::getline(std::cin, input);
        if (input.empty()) {
            symbol = default_symbol;
            break;
        } else if (input.size() > 1) {
            std::cout << "Entre un seul caractère stp" << std::endl;
            std::cout << "➤ ";
        } else {
            symbol = input[0];
            break;
        }
    }

    std::cout << std::endl;
    
    return symbol;
}

std::string ask_name() {
    std::cout << "Quel est ton nom ?" << std::endl;
    std::cout << "➤ ";

    std::string name {};

    // Verify input
    while (true) {
        std::getline(std::cin, name);
        if (!name.empty()) {
            break;
        }
        std::cout << "Entre un nom stp" << std::endl;
        std::cout << "➤ ";
    }

    std::cout << std::endl;
    
    return name;
}

std::string ask_coordinates(const std::string player_name, int max_size) {
    std::cout << player_name << ", à toi de jouer ! Où veux-tu placer ton symbole (ex: A1) ?" << std::endl;
    std::cout << "➤ ";

    std::string coordinates {};

    // Verify input
    while (true) {
        std::getline(std::cin, coordinates);
        if (coordinates.size() == 2) {
            if (coordinates[0] >= 'A' && coordinates[0] <= 'A' + max_size - 1) {
                if (coordinates[1] >= '1' && coordinates[1] <= '1' + max_size - 1) {
                    return coordinates;
                }
            }
        }
        std::cout << "Entre des coordonnées valides stp" << std::endl;
        std::cout << "➤ ";
    }
}


// =============
// DRAWING UTILS
// =============

void draw_title() {
    terminal_ctrl::clear_screen();
    std::cout << "╔═══════════╗" << std::endl;
    std::cout << "║ TICTACTOE ║" << std::endl;
    std::cout << "╚═══════════╝" << std::endl << std::endl;
}

void draw_game_board(const Board board, const int cell_size, char player_a_symbol, char player_b_symbol) 
{
    // Constants
    const int h_cell_size {cell_size + 1};      // Width of a cell in nb of characters (minus 1)
    const int v_cell_size {cell_size - 1};      // Height of a cell in nb of characters (minus 1)
    const int h_draw_size {board.size * h_cell_size};   // Full width of the board in number of characters
    const int v_draw_size {board.size * v_cell_size};   // Full height of the board in number of characters

    for (int j = 0; j <= h_draw_size; j++)
    {
        if((j + h_cell_size / 2) % h_cell_size == 0) {
            std::cout << static_cast<char>(j / h_cell_size + 65);
        }
        else {
            std::cout << ' '; 
        }
    }
    std::cout << std::endl;

    // for(CellState cell : board.cells) {
    //     switch (cell)
    //     {
    //         case CellState::EMPTY:
    //             std::cout << " ";
    //             break;

    //         case CellState::PLAYER_A:
    //             std::cout << player_a_symbol;
    //             break;

    //         case CellState::PLAYER_B:
    //             std::cout << player_b_symbol;
    //             break;
    //     }
    // }

    for (int i = 0; i <= v_draw_size; i++)
    {
        for (int j = 0; j <= h_draw_size; j++)
        {
            // First line
            if (i == 0) {
                if (j == 0) {
                    std::cout << "╔";
                } else if (j == h_draw_size ) {
                    std::cout << "╗";
                } else if (j % h_cell_size == 0) {
                    std::cout << "╦";
                } else {
                    std::cout << "═";
                }
            }
            // Last line
            else if (i == v_draw_size) {
                if (j == 0) {
                    std::cout << "╚";
                } else if (j == h_draw_size) {
                    std::cout << "╝";
                } else if (j % h_cell_size == 0) {
                    std::cout << "╩";
                } else {
                    std::cout << "═";
                }
            }
            // Middle lines
            else {
                if (i % v_cell_size == 0) {
                    if (j == 0) {
                        std::cout << "╠";
                    } else if (j == h_draw_size) {
                        std::cout << "╣";
                    } else if (j % h_cell_size == 0) {
                        std::cout << "╬";
                    } else {
                        std::cout << "═";
                    }
                } else {
                    if (j == h_draw_size) {
                        std::cout << "║ " << 1 + (i / v_cell_size);
                    } 
                    else if (j % h_cell_size == 0) {
                        std::cout << "║";
                    }
                    else {
                        if(j % h_cell_size == 2) {
                            char content = ' ';
                            if(board.cells[(i / v_cell_size) * board.size + (j / h_cell_size)] == CellState::PLAYER_A) {
                                content = player_a_symbol;
                            } 
                            else if(board.cells[(i / v_cell_size) * board.size + (j / h_cell_size)] == CellState::PLAYER_B) {
                                content = player_b_symbol;
                            }
                            std::cout << content;
                        } 
                        else {
                            std::cout << " ";
                        }
                    }
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}