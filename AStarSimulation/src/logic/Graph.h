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

class Graph : public sf::Drawable
{
	Context mContext;
	Node* mNodes = nullptr;
	uint8_t mWidth;
	uint8_t mHeight;
	bool mIsVisible;

	bool init_nodes(void);
public:
	Graph(uint8_t width, uint8_t height, Context context);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update_graph(const vec2i& coord);
	void show_graph(void);
	void hide_graph(void);
	bool get_visibility(void) const;
};
