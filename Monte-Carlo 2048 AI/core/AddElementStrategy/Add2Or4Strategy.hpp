#pragma once

#include <memory>

#include "Random/Random.hpp"
#include "IAddElementStrategy.hpp"

class Add2Or4Strategy : public IAddElementStrategy {
public:
    void AddElement(int& elementToSave) const override {
        constexpr auto limit = 10;
        std::make_unique<Random>()->GetNextInt(limit + 1) == limit ?
            (elementToSave = 4) :
            (elementToSave = 2);
    }
};
