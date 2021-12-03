#include "Game.hpp"
#include "Random/Random.hpp"
#include "utils/Utils.hpp"

using namespace std;
using namespace sf;

[[nodiscard]] int Game::GetElement(int row, int column) const {
    return this->field[row][column];
}

int Game::GetScore() const {
    return this->score;
}

bool Game::IsPlaying() const {
    return this->isPlaying;
}

void Game::MakeMove(Move move) {
    if (move == Move::NO) {
        return;
    }
    this->DirMove(MOVES.at(move));
}

void Game::InitBools() {
    this->isChanged  = false;
    this->isPlaying  = true;
}

void Game::InitScore() {
    this->score = 0;
}

void Game::InitElements() {
    for (auto& r : this->field) {
        for (auto& el : r) {
            el = 0;
        }
    }

    this->AddElement();
    this->AddElement();
}

void Game::AddElement() {
    auto row = 0, column = 0;
    auto rng = make_unique<Random>();

    do {
        row    = rng->GetNextInt(FIELD_SIZE);
        column = rng->GetNextInt(FIELD_SIZE);
    } while (this->field[row][column] != 0);

    // TODO: 25% chance to add 4
    this->addElement->AddElement(this->field[row][column]);
    ++this->elementsCount;
}

void Game::DirMove(const sf::Vector2i& direction) {
    this->isChanged = false;

    //std::clog << "Before move:\n";
    //std::for_each(this->field.begin(), this->field.end(),
    //    [](const auto& el) {
    //        PrintArray(el.begin(), el.end(), std::clog);
    //        std::clog << std::endl;
    //    }
    //);

    this->Shift(direction);

    //std::clog << "After first shift:\n";
    //std::for_each(this->field.begin(), this->field.end(),
    //    [](const auto& el) {
    //        PrintArray(el.begin(), el.end(), std::clog);
    //        std::clog << std::endl;
    //    }
    //);

    this->UniteSimilarTiles(direction);
    
    //std::clog << "After uniting:\n";
    //std::for_each(this->field.begin(), this->field.end(),
    //    [](const auto& el) {
    //        PrintArray(el.begin(), el.end(), std::clog);
    //        std::clog << std::endl;
    //    }
    //);

    this->Shift(direction);

    //std::clog << "After second shift (total):\n";
    //std::for_each(this->field.begin(), this->field.end(),
    //    [](const auto& el) {
    //        PrintArray(el.begin(), el.end(), std::clog);
    //        std::clog << std::endl;
    //    }
    //);
    //std::clog << std::string(35u, '-') << std::endl;

    if (this->isChanged) {
        this->AddElement();
        this->isPlaying = !this->CheckLose();
    }
}

void Game::Shift(const Vector2i& direction) {
    Vector2i a, b;
    auto normal = Vector2i(abs(direction.y), abs(direction.x));
    auto newDirection = Vector2i(direction.x < 0 ? 0 : direction.x,
        direction.y < 0 ? 0 : direction.y);

    for (auto i = 0; i < FIELD_SIZE; ++i) {
        a = i * normal + newDirection * (FIELD_SIZE - 1);

        for (auto j = 0; j < FIELD_SIZE; ++j) {
            auto& aElement = this->field[a.y][a.x];
            if (aElement == 0) {
                b = a - direction;

                for (auto k = j + 1; k < FIELD_SIZE; ++k) {
                    auto& bElement = this->field[b.y][b.x];
                    if (bElement != 0) {
                        aElement = bElement;
                        bElement = 0;
                        isChanged = true;
                        break;
                    }

                    b -= direction;
                }
            }

            a -= direction;
        }
    }
}

void Game::UniteSimilarTiles(const Vector2i& direction) {
    Vector2i a, b;
    auto normal = Vector2i(abs(direction.y), abs(direction.x));
    auto newDirection = Vector2i(direction.x < 0 ? 0 : direction.x,
        direction.y < 0 ? 0 : direction.y);

    for (auto i = 0; i < FIELD_SIZE; ++i) {
        a = i * normal + newDirection * (FIELD_SIZE - 1);

        for (auto j = 0; j < FIELD_SIZE - 1; ++j) {
            b = a - direction;
            auto& aElement = this->field[a.y][a.x];
            auto& bElement = this->field[b.y][b.x];

            if (aElement != 0 && aElement == bElement) {
                aElement += aElement;
                bElement = 0;

                if (aElement == WIN_VALUE) {
                    //this->isPlaying = false;
                }

                this->score     += aElement;
                this->isChanged = true;

                --this->elementsCount;
                ++j;

                a -= direction;
            }

            a -= direction;
        }
    }
}

bool Game::CheckLose() {
    std::clog << "Check lose start:...";
    std::clog << "1";

    if (this->elementsCount < FIELD_SIZE * FIELD_SIZE) {
        std::clog << "...check lose end!\n";
        return false;
    }

    std::clog << "2";
    auto isMovable = false;

    for (auto i = 0; i < FIELD_SIZE - 1; ++i) {
        for (auto j = 0; j < FIELD_SIZE - 1; ++j) {
            if (this->field[i][j] == this->field[i + 1][j]
                ||
                this->field[i][j] == this->field[i][j + 1]) {
                isMovable = true;
                goto outOffLoop;
            }
        }
    }
    outOffLoop:
    std::clog << "3";

    if (isMovable) {
        std::clog << "...check lose end!\n";
        return false;
    }

    std::clog << "4";

    for (auto i = 0; i < FIELD_SIZE - 1; ++i) {
        if (this->field[i][FIELD_SIZE - 1] == this->field[i + 1][FIELD_SIZE - 1]
            ||
            this->field[FIELD_SIZE - 1][i] == this->field[FIELD_SIZE - 1][i + 1]) {
            isMovable = true;
            break;
        }
    }

    std::clog << "5";

    std::clog << "...check lose end!\n";
    return !isMovable;
}
