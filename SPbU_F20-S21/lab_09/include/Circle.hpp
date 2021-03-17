#pragma once

#include "Figure.hpp"
#include <algorithm>
#include <cstring>

class Circle : public Figure {
public:
    Circle(int id, int x, int y, int radius, const char* label);
    ~Circle();

    void print() const override;
    bool is_inside(int x, int y) const override;
    void zoom(int factor) override;

    // ...

private:
    const char* label;
    int radius;
};
