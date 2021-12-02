#pragma once

#include "Game/Move.hpp"

struct IGetMoveStrategy {
public:
    [[nodiscard]] virtual Move GetMove() = 0;
};
