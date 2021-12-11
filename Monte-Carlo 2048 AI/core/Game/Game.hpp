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

        //this->field[0][0] = 4;
        //this->field[0][1] = 8;
        //this->field[0][2] = 16;
        //this->field[0][3] = 32;

        //this->field[1][0] = 512;
        //this->field[1][1] = 256;
        //this->field[1][2] = 128;
        //this->field[1][3] = 64;

        //this->field[2][0] = 1024;
        //this->field[2][1] = 2048;
        //this->field[2][2] = 4096;
        //this->field[2][3] = 8192;

        //this->field[3][0] = 131'072;
        //this->field[3][1] = 131'072 / 2;
        //this->field[3][2] = 131'072 / 2 / 2;
        //this->field[3][3] = 131'072 / 2 / 2 / 2;

        //this->score = 3'869'064;
    }

    Game(const Game&) = default;

    Game(Game&&) noexcept = default;

    [[nodiscard]] int GetElement(int row, int column) const;
    [[nodiscard]] int GetScore() const;

    [[nodiscard]] std::array<std::array<int, FIELD_SIZE>, FIELD_SIZE> GetField() const;

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
