#pragma once

#include <iostream>

#include "AI2048/AI.hpp"
#include "Random/Random.hpp"
#include "const/Const.hpp"

#include <fmt/format.h>
#include <future>
#include <chrono>

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

        auto begin = std::chrono::steady_clock::now();

        for (auto i = 0; i < moves.size(); ++i) {
            //std::clog << std::string(35, '-') + "\n";
            //std::clog << fmt::format("Move: {}\n", MoveToString(moves[i]));
            auto tempScore = 0.0;
            std::vector<std::future<void>> tasks;

            for (auto j = 0; j < this->simulationsCount; ++j) {
                tasks.push_back(std::async(std::launch::async, [this, &game, &random, &i, &j, &moves, &tempScore]() {
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

                    tempScore += tempGame.GetScore();
                    //std::clog << fmt::format("Simulation #{}. Score: {}. Thread {}\n", j + 1, tempGame.GetScore(), std::hash<std::thread::id>{}(std::this_thread::get_id()));
                }));
            }

            std::for_each(tasks.begin(), tasks.end(), [](auto& task) { task.wait(); });

            tempScore /= this->simulationsCount;
            //std::clog << fmt::format("Math. expect: {}\n", tempScore);

            if (tempScore >= bestScore) {
                bestScore = tempScore;
                bestMove  = moves[i];
            }

            //std::clog << std::string(35, '-') + "\n";
        }

        auto end = std::chrono::steady_clock::now();
        //std::clog << fmt::format("TIME: {} ms.\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());

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
