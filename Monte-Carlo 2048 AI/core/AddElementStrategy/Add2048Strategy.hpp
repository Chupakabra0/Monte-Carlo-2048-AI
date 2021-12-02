#pragma once

#include "IAddElementStrategy.hpp"

class Add2048Strategy : public IAddElementStrategy {
public:
    void AddElement(int& elementToSave) const override {
        elementToSave = 2048;
    }
};
