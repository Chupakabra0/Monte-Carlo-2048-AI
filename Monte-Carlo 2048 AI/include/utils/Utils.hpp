#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "const/Const.hpp"

static sf::Color GetTileColor(int points) {
    return points == 0 ? sf::Color::Black : TILE_COLORS[static_cast<decltype(TILE_COLORS)::size_type>(log2(points) - 1)];
}

template<class Iter>
static void PrintArray(Iter begin, Iter end, std::ostream& out) {
    auto size = std::distance(begin, end);

    if (size == 0) {
        return;
    }

    out << "[ " << *begin++;

    while (begin != end) {
        out << ", " << *begin++;
    }
    out << " ]";
}
