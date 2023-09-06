#include "libs.hpp"

Map::Map() : graph() {
    if (!texture.loadFromFile("media/map.png")) { throw std::runtime_error{"file do not exist"}; }
    texture.setSmooth(true);
    sprite.setTexture(texture);

    character = std::make_shared<Character>();
    placeCharacter(0);
}

void Map::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
    character->draw(window);
}

void Map::save(std::ostream& os) const {
    character->save(os);
}

void Map::update(float dt) {
    character->update(dt);
    if (character->isMoving) {
        deltaT += dt;
        while (deltaT > 0.15) {
            deltaT -= 0.15;
            placeCharacter(path[0]);
            path.erase(path.begin());
            if (path.empty()) {
                character->isMoving = false;
                deltaT = 0;
                return;
            }
        }
    }
}

void Map::load(std::istream& is) {
    unsigned vertex, state, frame;
    float dt;
    is >> vertex >> state >> frame >> dt;
	character = std::make_shared<Character>(static_cast<State>(state), frame, dt);
	placeCharacter(vertex);
}

void Map::placeCharacter(unsigned vertex) {
    character->vertex = vertex;
    auto box = getPosition(vertex);
    character->setPosition(box);
}

void Map::changeCharacterState(sf::Event event) {
    character->changeState(event);
}

bool Map::characterIsMoving() const {
    return character->isMoving;
}

void Map::characterWillMove() {
    character->isMoving = true;
}

unsigned Map::characterVertex() const {
    return character->vertex;
}

bool Map::isVertex(int x, int y) const {
	for(auto v : graph.vertices)
		if (v.contains(x, y))
			return true;
	return false;
}

unsigned Map::getIndex(int x, int y) const {
	int i;
    for(i = 0; i < graph.size; i++) {
		auto box = graph.vertices[i];
		if (box.contains(x, y))
			break;
	}
	return i;
}

Position Map::getPosition(unsigned i) const {
	auto rect = graph.getVertex(i);
    return {int(rect.left + rect.width / 2), int(rect.top + rect.height / 2)};
}

std::vector<unsigned> Map::pathTo(unsigned destiny) const {
	return graph.dijkstra(character->vertex, destiny);
}

void Map::setPathTo(unsigned destiny) {
    path = pathTo(destiny);
	path.erase(path.begin());
}