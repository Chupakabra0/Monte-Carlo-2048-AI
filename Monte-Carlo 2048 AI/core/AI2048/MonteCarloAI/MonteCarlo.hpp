#pragma once

#include <iostream>

#include "AI2048/AI.hpp"
#include "Random/Random.hpp"

#include <fmt/format.h>

class MonteCarloAI : public AI {
public:
    explicit MonteCarloAI(int simulationsCount = 20, int maxGameLength = 100)
        : simulationsCount(simulationsCount), maxGameLength(maxGameLength) {

    }

    ~MonteCarloAI() override = default;

    [[nodiscard]] Move GetBestMove(const Game& game) override {
        const auto moves = this->GetAvailiableMoves(game);
        const auto random = std::make_unique<Random>();

        auto bestMove  = moves.empty() ? Move::NO : moves.front();
        auto bestScore = game.GetScore();

        for (auto i = 0; i < moves.size(); ++i) {
            //std::clog << std::string(35, '-') << std::endl;
            //std::clog << fmt::format("Move: {}", MoveToString(moves[i])) << std::endl;
            auto tempScore = 0;

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

                //std::clog << fmt::format("Simulation #{}. Score: {}.", j + 1, tempGame.GetScore()) << std::endl;
                tempScore += tempGame.GetScore();
            }

            tempScore /= this->simulationsCount;
            //std::clog << fmt::format("Math. expect: {}", tempScore) << std::endl;

            if (tempScore >= bestScore) {
                bestScore = tempScore;
                bestMove  = moves[i];
            }

            //std::clog << std::string(35, '-') << std::endl;
        }

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