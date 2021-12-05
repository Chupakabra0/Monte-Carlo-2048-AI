#pragma once
#include "const/Const.hpp"

#include <array>
#include "AddElementStrategy/Add2Or4Strategy.hpp"
#include "AddElementStrategy/Add2Strategy.hpp"
#include "Game/Move.hpp"

class Game {
public:
    explicit Game() : addElement(new Add2Or4Strategy) {
        this->InitBools();
        this->InitScore();
        this->InitElements();

        this->field[0][0] = 4096;
        this->field[0][1] = 4096 * 2;
        this->field[0][2] = 4096 * 2 * 2;
        this->field[0][3] = 4096 * 2 * 2 * 2;
        this->field[1][0] = 4096 * 2 * 2 * 2 * 2;
        this->field[1][1] = 4096 * 2 * 2 * 2 * 2 * 2;
    }

    Game(const Game&) = default;

    Game(Game&&) noexcept = default;

    [[nodiscard]] int GetElement(int row, int column) const;
    [[nodiscard]] int GetScore() const;

    [[nodiscard]] bool IsPlaying() const;
    [[nodiscard]] bool IsChanged() const;

    void MakeMove(Move move);

private:
    bool isPlaying;
    bool isChanged;

    int score{};
    int elementsCount{};

    std::shared_ptr<IAddElementStrategy> addElement;

    std::array<std::array<int, FIELD_SIZE>, FIELD_SIZE> field;

    //--------------------- INITS -----------------------//

    void InitBools();
    void InitScore();
    void InitElements();

    //--------------------- GAME ------------------------//

    //void AddStartingElement();
    void AddElement();
    void DirMove(const sf::Vector2i& direction);
    void Shift(const sf::Vector2i& direction);
    void UniteSimilarTiles(const sf::Vector2i& direction);
    bool CheckLose();
};
