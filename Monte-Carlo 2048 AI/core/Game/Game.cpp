#include "Game.hpp"
#include "Random/Random.hpp"

using namespace std;

[[nodiscard]] int Game::GetElement(int row, int column) const {
    return this->field[row][column];
}

void Game::MakeMove(Move move) {
    // shift

    // add similar tiles

    // shift

    // spawn new tile if the game is not over
}

void Game::InitBools() {
    this->isChanged  = false;
    this->isWin     = false;
    this->isPlaying = true;
}

void Game::InitScore() {
    this->score = 0;
}

void Game::InitElements() {
    this->elementsCount = START_COUNT;
    
    for (auto& r : this->field) {
        for (auto& el : r) {
            el = 0;
        }
    }

    this->AddStartingElement();
}

void Game::AddStartingElement() {
    auto row = 0, column = 0;
    auto rng = make_unique<Random>();

    for (auto i = 0; i < START_COUNT; ++i) {
        do {
            row    = rng->GetNextInt(FIELD_SIZE);
            column = rng->GetNextInt(FIELD_SIZE);
        } while (this->field[row][column] != 0);

        // TODO: 25% chance to add 4
        this->addElement->AddElement(this->field[row][column]);
        //this->field[row][column] = 2048;
    }
}
