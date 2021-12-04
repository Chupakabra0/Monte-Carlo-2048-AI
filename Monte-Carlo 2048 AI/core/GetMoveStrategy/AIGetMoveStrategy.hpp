#pragma once

#include <memory>

#include "AI2048/MonteCarloAI/MonteCarlo.hpp"
#include "GetMoveStrategy/IGetMoveStrategy.hpp"

class AIGetMoveStrategy : public IGetMoveStrategy {
public:
    explicit AIGetMoveStrategy(const std::shared_ptr<AI>& ai) : ai(ai) {
    
    }

    [[nodiscard]] Move GetMove(const Game& game) override {
        return ai->GetBestMove(game);
    }

private:
    std::shared_ptr<AI> ai;
};
