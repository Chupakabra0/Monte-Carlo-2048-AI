#pragma once

#include <SFML/Graphics.hpp>

#include "const/Const.hpp"

static sf::Color GetTileColor(int points) {
    return TILE_COLORS[static_cast<decltype(TILE_COLORS)::size_type>(log2(points) - 1)];
}
