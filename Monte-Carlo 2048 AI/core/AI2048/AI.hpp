#pragma once

#include "Game/Game.hpp"

struct AI {
public:
    virtual ~AI() = default;

    [[nodiscard]] virtual Move GetBestMove(const Game& game) = 0;
};
