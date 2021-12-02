#pragma once

#include "IAddElementStrategy.hpp"

class Add2Strategy : public IAddElementStrategy {
public:
    void AddElement(int& elementToSave) const override {
        elementToSave = 2;
    }
};
