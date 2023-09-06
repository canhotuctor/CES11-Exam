#include "libs.hpp"

#include <cmath>
#include <iostream>
#include <fstream>
#include <stack>
#include <limits>

Graph::Graph() {
	std::ifstream inputPosits("config/collisionBoxes");
	if (inputPosits.is_open()) {
		inputPosits >> size;
		//initializing the vertices
		for (int i = 0; i < 14; ++i) {
			unsigned x1, y1, x2, y2;
			inputPosits >> x1 >> y1 >> x2 >> y2;
			vertices[i] = sf::Rect<unsigned>(x1, y1, x2 - x1, y2 - y1);
		}
	}

	std::ifstream inputEdges("config/graphEdges");
	if (inputEdges.is_open()) {
		// initializing the edges
		unsigned edgeA, edgeB;
		while(inputEdges >> edgeA >> edgeB)
			addEdge(edgeA, edgeB);
	}

}

bool Graph::checkEdge(unsigned from, unsigned to) const {
	if(from == to) return false;

	if(from > to)
		std::swap(from, to);

	for(unsigned edge : list_adj[from])
		if(edge == to)
			return true;

	return false;
}

void Graph::addEdge(unsigned from, unsigned to) {
	if(from == to) return;
	if(from > to)
		std::swap(from, to);
	if(checkEdge(from, to))
		return;
	list_adj[from].push_back(to);
}

void Graph::delEdge(unsigned from, unsigned to) {
	if(from > to)
		std::swap(from, to);

	if(!checkEdge(from, to))
		return;

   for(unsigned i = 0; i < list_adj[from].size(); i++)
		if(list_adj[from][i] == to)
			list_adj[from].erase(list_adj[from].begin() + i);
}

std::vector<unsigned> Graph::dijkstra(unsigned origin, unsigned destiny) const {
	unsigned x, y;
	std::array<unsigned, 14> predecessors{};
	std::array<bool, 14> visited{};
	std::array<float, 14> minimum_dist{};

	predecessors.fill(origin);
	visited.fill(false);
	minimum_dist.fill(std::numeric_limits<float>::infinity());
	minimum_dist[origin] = 0;

	for (int i = 1; i <= 14; i++) {
		float d_min = std::numeric_limits<float>::infinity();
		for (y = 0; y < 14; y++) {
			if ((!visited[y]) && (d_min >= minimum_dist[y])) {
				d_min = minimum_dist[y];
				x = y;
			}
		}
		visited[x] = true;
		for (unsigned j = 0; j < 14; j++) {
			if(!checkEdge(x, j)) continue;

			if ((!visited[j]) && (minimum_dist[j] > (1 + minimum_dist[x]))) {
				minimum_dist[j] = 1 + minimum_dist[x];
				predecessors[j] = x;
			}
		}
	}

	x = destiny;
	std::stack<unsigned> way;

	while (x != origin) {
		way.push(x);
		x = predecessors[x];
		if(x == origin)
			way.push(origin);
	}

	// inverting the stack
	std::vector<unsigned> the_way;
	while (!way.empty()) {
		the_way.push_back(way.top());
		way.pop();
	}
	return the_way;
}

const sf::Rect<unsigned>& Graph::getVertex(unsigned v) const {
	return vertices[v];
}
