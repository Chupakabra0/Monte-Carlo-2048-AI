#pragma once

#include <SFML/Graphics.hpp>
#include "GetMoveStrategy/IGetMoveStrategy.hpp"

class KeyboardGetMoveStrategy : IGetMoveStrategy {
public:
    explicit KeyboardGetMoveStrategy(sf::Event e) : e(e) {

    }

    [[nodiscard]] Move GetMove(const Game&) override {
        auto gameMove = Move::NO;
        if (e.type == sf::Event::KeyReleased) {
            switch (e.key.code) {
                case sf::Keyboard::Up: {
                    gameMove = Move::UP;
                    break;
                }
                case sf::Keyboard::Down: {
                    gameMove = Move::DOWN;
                    break;
                }
                case sf::Keyboard::Left: {
                    gameMove = Move::LEFT;
                    break;
                }
                case sf::Keyboard::Right: {
                    gameMove = Move::RIGHT;
                    break;
                }
                default: {
                    break;
                }
            }
        }

        return gameMove;
    }

private:
    sf::Event e;
};
