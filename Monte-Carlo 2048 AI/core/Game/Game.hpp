#pragma once
#include "const/Const.hpp"

#include <array>

class Game {
public:
    explicit Game() {
        this->InitBools();
        this->InitElements();
        this->InitScore();
    }

    Game(const Game&) = default;

    Game(Game&&) noexcept = default;

    [[nodiscard]] std::array<std::array<int, FIELD_SIZE>, FIELD_SIZE> GetField() const {
        return this->field;
    }

private:
    bool isPlaying;
    bool isWin;
    bool isChanged;

    int score;
    int elementsCount;

    std::array<std::array<int, FIELD_SIZE>, FIELD_SIZE> field;

    //--------------------- INITS -----------------------//

    void InitBools();
    void InitScore();
    void InitElements();

    //--------------------- GAME ------------------------//

    void AddStartingElement();
};
