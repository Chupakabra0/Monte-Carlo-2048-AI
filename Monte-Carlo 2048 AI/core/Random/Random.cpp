#include "Random.hpp"

[[nodiscard]] int Random::GetNextInt() {
    return this->GetNextInt(std::numeric_limits<int>::max());
}

[[nodiscard]] int Random::GetNextInt(int high) {
    return this->GetNextInt(0, high);
}

[[nodiscard]] int Random::GetNextInt(int low, int high) {
    std::uniform_int_distribution<int> roll(low, high - 1);
    return roll(this->randomGenerator);
}
