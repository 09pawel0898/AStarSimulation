#pragma once

#include "../states/State.h"

typedef States::State::Context Context;

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
};

class Graph
{
public:
	uint8_t WIDTH;
	uint8_t HEIGHT;

private:
	Context mContext;
	Node* mNodes = nullptr;

	//bool mIsVisible;

	bool init_nodes(void);
public:
	Graph(uint8_t width, uint8_t height, Context context);
	void update_graph(const vec2i& coord);
	Node* get_nodes(void) const;
};

