#include "libs.hpp"

Character::Character() {
    if (!defaultTexture.loadFromFile("media/defaultBarriguinha.png")) { throw std::runtime_error{"file do not exist"}; }
    defaultTexture.setSmooth(true);
    defaultSprite.setTexture(defaultTexture);
    defaultSprite.setScale(0.1, 0.1);
    defaultSprite.setOrigin(350, 854);
    
    if (!danceTexture.loadFromFile("media/danceBarriguinha.png")) { throw std::runtime_error{"file do not exist"}; }
    danceTexture.setSmooth(true);

    std::vector<sf::Color> color = {
        sf::Color::Red, 
        sf::Color::Magenta, 
        sf::Color::Blue, 
        sf::Color::Cyan, 
        sf::Color::Green, 
        sf::Color::Yellow
    };

    for(unsigned y = 0; y < 6; ++y) {
        for (unsigned x = 0; x < 7; ++x) {
            sf::Sprite sprite(danceTexture, sf::IntRect(112 * x, 112 * y, 112, 112));
            sprite.setScale(0.8, 0.8);
            sprite.setOrigin(56, 112);
            danceSprites.push_back(sprite);

            sprite.setColor(color[x % 6]);
            crazySprites.push_back(sprite);
        }
    }

    if (!spinTexture.loadFromFile("media/spinBarriguinha.png")) { throw std::runtime_error{"file do not exist"}; }
    spinTexture.setSmooth(true);
    for(unsigned y = 0; y < 3; ++y) {
        for (unsigned x = 0; x < 5; ++x) {
            sf::Sprite sprite(spinTexture, sf::IntRect(320 * x, 569 * y, 320, 569));
            sprite.setScale(0.35, 0.35);
            sprite.setOrigin(160, 385);
            spinSprites.push_back(sprite);
        }
    }
}

Character::Character(State state, unsigned frame, float deltaT) : Character() {
    this->state = state;
    this->frame = frame;
    this->deltaT = deltaT;
}

void Character::draw(sf::RenderWindow& window) const {
    switch(state) 
    {
    case State::Default:
        window.draw(defaultSprite);
        return;
    case State::Dance:
        window.draw(danceSprites[frame]);
        return;
    case State::Crazy:
        window.draw(crazySprites[frame]);
        return;
    case State::Spin:
        window.draw(spinSprites[frame]);
    }
}

void Character::save(std::ostream& os) const {
    os << vertex << '\n' << static_cast<unsigned>(state) << '\n' << frame << '\n' << deltaT << '\n';
}

void Character::update(float dt) {
    switch(state) 
    {
    case State::Default:
        return;
    case State::Dance:
        changeFrame(danceSprites, 0.05, dt);
        return;
    case State::Crazy:
        changeFrame(crazySprites, 0.02, dt);
        return;
    case State::Spin:
        changeFrame(spinSprites, 0.025, dt);
        return;
    }
}

void Character::setPosition(Position pos) {
    defaultSprite.setPosition(pos.x,pos.y);
    for (auto& sprites : danceSprites)
        sprites.setPosition(pos.x,pos.y);
    for (auto& sprites : crazySprites)
        sprites.setPosition(pos.x,pos.y);
    for (auto& sprites : spinSprites)
        sprites.setPosition(pos.x,pos.y);
}

void Character::changeFrame(std::vector<sf::Sprite>& sprites, float updateRate, float dt) {
    deltaT += dt;
    while (deltaT > updateRate) {
        deltaT -= updateRate;
        frame = (frame == sprites.size() - 1 ? 0 : frame + 1);
    }
}

void Character::changeState(sf::Event event) {
    frame = 0;
    if (event.key.code == sf::Keyboard::D) 
        swapState(State::Dance);
    else if (event.key.code == sf::Keyboard::C) 
        swapState(State::Crazy);
    else if (event.key.code == sf::Keyboard::S) 
        swapState(State::Spin);
}

void Character::swapState(State st) {
    if (state != st)
        state = st;
    else 
        state = State::Default;
}