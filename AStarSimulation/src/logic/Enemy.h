#pragma once

#include "../states/State.h"
#include "Animation.h"

class Graph;
class PathFinder;

typedef States::State::Context Context;

enum class AnimID
{
	WALK,
	IDLE
};

class Enemy : public sf::Drawable
{
private:
	Context* mContext;
	PathFinder* mPathFinder;

	std::unordered_map<AnimID, Animation> mAnims;
	std::unordered_map<AnimID, Animation>::iterator mCurrentAnim;
	AnimID mCurrentAnimID;
	std::list<vec2i>& mCoordsTakenOnTheGrid;

	vec2i mGridPosition;
	vec2f mPosition;
	bool mPathExist;
	bool mPause;


	void init_animations(void);

public:
	Graph* mGraph;

	Enemy(Context context, Graph* graph, std::list<vec2i>& coordsTakenByEnemies);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(const sf::Time& dt);
	PathFinder& get_path_finder(void) const;
	Graph* get_graph(void);
};