#pragma once
#include <random>

class Random {
public:
    explicit Random() = default;

    Random(const Random&) = default;

    Random(Random&&) noexcept = default;

    virtual ~Random() = default;

    [[nodiscard]] int GetNextInt();
    [[nodiscard]] int GetNextInt(int high);
    [[nodiscard]] int GetNextInt(int low, int high);

private:
    std::default_random_engine randomGenerator;
};

