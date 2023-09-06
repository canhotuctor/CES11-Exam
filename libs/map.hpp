#pragma once

#include "drawable.hpp"
#include "character.hpp"
#include "graph.hpp"

#include <memory>
#include <iostream>

class Map : public Drawable {
private:
    sf::Texture texture;
    sf::Sprite sprite;

    Graph graph;

	std::shared_ptr<Character> character;
    float deltaT = 0.0;
	std::vector<unsigned> path; 

public:
    Map();

    void draw(sf::RenderWindow&) const override;
    void save(std::ostream&) const override;
    void update(float) override;

    void load(std::istream&);

    void placeCharacter(unsigned);
    void changeCharacterState(sf::Event);
    bool characterIsMoving() const;
    void characterWillMove();
    unsigned characterVertex() const;

    bool isVertex(int x, int y) const; 
	unsigned getIndex(int x, int y) const;
	Position getPosition(unsigned) const;
	std::vector<unsigned> pathTo(unsigned) const;
    void setPathTo(unsigned);
};