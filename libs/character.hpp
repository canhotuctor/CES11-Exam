#pragma once

#include "drawable.hpp"

#include <memory>

enum class State {
    Default,
    Dance,
    Crazy,
    Spin,
};

class Character : public Drawable {
private:
    sf::Texture defaultTexture, danceTexture, spinTexture;
    sf::Sprite defaultSprite;
    std::vector<sf::Sprite> danceSprites, crazySprites, spinSprites;
    
    unsigned frame = 0;
    float deltaT = 0.0;
    State state = State::Default;

    void swapState(State);
    void changeFrame(std::vector<sf::Sprite>&, float, float);

public:
    bool isMoving = false;
    unsigned vertex = 0;
    
    Character();
    Character(State, unsigned, float);

    void draw(sf::RenderWindow&) const override;
    void save(std::ostream&) const override;
    void update(float) override;

    void setPosition(Position);
    void changeState(sf::Event);
};