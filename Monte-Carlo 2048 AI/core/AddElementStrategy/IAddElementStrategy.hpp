#pragma once

struct IAddElementStrategy {
public:
    virtual ~IAddElementStrategy() = default;
    virtual void AddElement(int&) const = 0;
};
