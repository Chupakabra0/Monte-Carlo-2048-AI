#pragma once

#include <iostream>

#include "AI2048/AI.hpp"
#include "Random/Random.hpp"
#include "const/Const.hpp"

#include <fmt/format.h>

class MonteCarloAI : public AI {
public:
    explicit MonteCarloAI(int simulationsCount = DEFAULT_SIMULATIONS_COUNT, int maxGameLength = DEFAULT_MAX_LENGTH_GAME)
        : simulationsCount(simulationsCount), maxGameLength(maxGameLength) {

    }

    ~MonteCarloAI() override = default;

    [[nodiscard]] Move GetBestMove(const Game& game) override {
        const auto moves = this->GetAvailiableMoves(game);
        const auto random = std::make_unique<Random>();

        auto bestMove  = moves.empty() ? Move::NO : moves.front();
        auto bestScore = static_cast<double>(game.GetScore());

        //std::clog << fmt::format("Get move started\n");

        for (auto i = 0; i < moves.size(); ++i) {
            //std::clog << std::string(35, '-') + "\n";
            //std::clog << fmt::format("Move: {}\n", MoveToString(moves[i]));
            auto tempScore = 0.0;

            for (auto j = 0; j < this->simulationsCount; ++j) {
                auto tempGame = game;
                tempGame.MakeMove(moves[i]);

                for (auto k = 0; k < this->maxGameLength && tempGame.IsPlaying(); ) {
                    const auto tempAvailiableMoves = this->GetAvailiableMoves(tempGame);
                    const auto tempMove
                        = tempAvailiableMoves[random->GetNextInt(tempAvailiableMoves.size())];
                    
                    tempGame.MakeMove(tempMove);

                    if (tempGame.IsChanged()) {
                        ++k;
                    }
                }

                //std::clog << fmt::format("Simulation #{}. Score: {}\n", j + 1, tempGame.GetScore());
                tempScore += tempGame.GetScore();
            }

            tempScore /= this->simulationsCount;
            //std::clog << fmt::format("Math. expect: {}\n", tempScore);

            if (tempScore >= bestScore) {
                bestScore = tempScore;
                bestMove  = moves[i];
            }

            //std::clog << std::string(35, '-') + "\n";
        }

        //std::clog << fmt::format("BEST MOVE: {} (score {})\n", MoveToString(bestMove), bestScore);
        //std::clog << fmt::format("Get move ended\n");
        //std::clog << std::string(35, '-') + "\n" << std::flush;

        return bestMove;
    }

private:
    int simulationsCount;
    int maxGameLength;

    [[nodiscard]] std::vector<Move> GetAvailiableMoves(const Game& game) const {
        const std::array<Move, 4> moves{ Move::DOWN, Move::LEFT, Move::RIGHT, Move::UP };
        std::vector<Move> result;
        
        for (auto move : moves) {
            auto tempGame = game;
            tempGame.MakeMove(move);

            if (tempGame.IsChanged()) {
                result.push_back(move);
            }
        }

        return result;
    }
};