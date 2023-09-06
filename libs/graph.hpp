#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>

class Graph {
	friend class Map;
private:
	unsigned size;

	//stores existent edges, with each vector containing the edges with vertices greater than self
	std::array<std::vector<unsigned>, 14> list_adj;

	std::array<sf::Rect<unsigned>, 14> vertices;

	const sf::Rect<unsigned>& getVertex(unsigned) const;

	bool checkEdge(unsigned, unsigned) const;
	void addEdge(unsigned, unsigned);
	void delEdge(unsigned, unsigned);

public:
	Graph();

	// returns the shortest path between the given points
	std::vector<unsigned> dijkstra(unsigned origin, unsigned destiny) const;
};
