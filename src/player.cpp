#include <settings.hpp>
#include <string>
#include "ui.hpp"

struct Player {
    std::string name {};
    char symbol {};
};

Player create_player(const char default_symbol) {
    std::string name {ask_name()};
    char symbol {ask_symbol(default_symbol)};
    Player p {name, symbol};
    return p;
}