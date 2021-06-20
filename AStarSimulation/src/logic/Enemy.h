#pragma once

#include "../states/State.h"

class Graph;
class PathFinder;
typedef States::State::Context Context;

class Enemy : public sf::Drawable
{
private:
	Context* mContext;
	Animation* mAnimation;
	
	PathFinder* mPathFinder;

	vec2i mGridPosition;
	vec2i windowPosition;

public:
	Graph* mGraph;
	Enemy()
	{}
	Enemy(Context context, Graph* graph);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	PathFinder& get_path_finder(void) const;
	Graph* get_graph(void);
};