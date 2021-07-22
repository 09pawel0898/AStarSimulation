#pragma once

#include "../states/State.h"

struct Node
{
	int x;
	int y;

	bool obstacle = false;
	bool visited = false;
	float globalGoal;
	float localGoal;
	std::vector<Node*> neighbours;
	Node* parent = nullptr;

	Node() {}
	Node(int x,int y) 
		: x(x), y(y) {}
	bool operator ==(const Node& rhs) const
	{
		return this->x == rhs.x && this->y == rhs.y;
	}
};

class Graph
{
public:
	uint8_t WIDTH;
	uint8_t HEIGHT;

private:
	Node* mNodes = nullptr;
	bool init_nodes(void);

public:
	Graph(uint8_t width, uint8_t height);
	void update_graph(const vec2i& coord);
	Node* get_nodes(void) const;
};

