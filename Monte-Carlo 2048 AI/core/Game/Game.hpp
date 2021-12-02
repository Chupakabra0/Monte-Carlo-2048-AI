#pragma once
#include "const/Const.hpp"

#include <array>
#include "AddElementStrategy/Add2Strategy.hpp"
#include "Game/Move.hpp"

class Game {
public:
    explicit Game() : addElement(new Add2Strategy) {
        this->InitBools();
        this->InitElements();
        this->InitScore();
    }

    Game(const Game&) = default;

    Game(Game&&) noexcept = default;

    [[nodiscard]] int GetElement(int row, int column) const;

    void MakeMove(Move move);

private:
    bool isPlaying;
    bool isWin;
    bool isChanged;

    int score;
    int elementsCount;

    std::unique_ptr<IAddElementStrategy> addElement;

    std::array<std::array<int, FIELD_SIZE>, FIELD_SIZE> field;

    //--------------------- INITS -----------------------//

    void InitBools();
    void InitScore();
    void InitElements();

    //--------------------- GAME ------------------------//

    void AddStartingElement();
};
