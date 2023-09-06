#pragma once

#include <SFML/Graphics.hpp>

class Drawable {
public:
    virtual void draw(sf::RenderWindow&) const = 0;
    virtual void save(std::ostream&) const = 0;
    virtual void update(float) = 0;
};

struct Position {
    int x, y;
    bool operator<(const Position& other) const {
        if (x < other.x)
            return true;
        if (x == other.x)
            return y < other.y;
        return false;
    }
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};