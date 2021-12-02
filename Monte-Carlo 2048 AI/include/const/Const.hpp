#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "Game/Move.hpp"

static constexpr auto WINDOW_MARGIN  = 100;
static constexpr auto WINDOW_WIDTH   = 400;
static constexpr auto WINDOW_HEIGHT  = WINDOW_WIDTH + WINDOW_MARGIN;

static constexpr auto FIELD_SIZE  = 4;
static constexpr auto START_COUNT = 2;

static constexpr auto TILE_SIZE    = WINDOW_WIDTH / FIELD_SIZE;
static constexpr auto TILE_PADDING = 5;
static constexpr auto WIN_VALUE    = 2048;

static constexpr auto TILE_COLORS_SIZE = 11;
static const std::array<sf::Color, TILE_COLORS_SIZE> TILE_COLORS = {
    sf::Color(250, 231, 224),
    sf::Color(249, 225, 206),
    sf::Color(249, 179, 124),
    sf::Color(246, 149, 96),
    sf::Color(243, 125, 95),
    sf::Color(254, 92, 65),
    sf::Color(245, 208, 119),
    sf::Color(249, 208, 103),
    sf::Color(249, 202, 88),
    sf::Color(239, 196, 65),
    sf::Color(244, 198, 42)
};

static const std::map<Move, sf::Vector2i> MOVES = {
    std::make_pair(Move::DOWN, sf::Vector2i(0, 1)),
    std::make_pair(Move::LEFT, sf::Vector2i(-1, 0)),
    std::make_pair(Move::RIGHT, sf::Vector2i(1, 0)),
    std::make_pair(Move::UP, sf::Vector2i(0, -1)),
    std::make_pair(Move::NO, sf::Vector2i(0, 0))
};
