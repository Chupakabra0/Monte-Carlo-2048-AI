#pragma once

#include "Game/Move.hpp"

struct IGetMoveStrategy {
public:
    [[nodiscard]] virtual Move GetMove(const Game&) = 0;
};
