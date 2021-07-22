#pragma once

#include "../states/State.h"
#include "Animation.h"
#include "PathFinder.h"

class Graph;
class PathFinder;

typedef States::State::Context Context;

enum class AnimID
{
	WALK,
	IDLE
};

struct DirectionVector
{
	Direction dir;
	vec2f vec;
};

class Enemy : public sf::Drawable
{
private:
	Context* mContext;
	PathFinder* mPathFinder;
	Direction mCurrentDir;

	std::map<Direction, vec2f> mDirections;
	std::unordered_map<AnimID, Animation> mAnims;
	std::unordered_map<AnimID, Animation>::iterator mCurrentAnim;
	AnimID mCurrentAnimID;

	vec2i mGridPosition;
	vec2f mPosition;
	vec2f mCurrentDestinationPoint;
	bool mPathExist;
	bool mPause;
	double mSpeed; 

	void init_random_position(std::list<vec2i>& coordsTakenByEnemies);
	void init_components(void);
	void init_animations(void);
	void init_directions(void);

	bool set_anim(AnimID newAnim);
public:
	Graph* mGraph;

	Enemy(Context context, Graph* graph, std::list<vec2i>& coordsTakenByEnemies);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(const sf::Time& dt);
	void update_rotation(void);
	vec2i Enemy::update_grid_position(void);
	bool move(const sf::Time& dt);
	void switch_pause(void);
	PathFinder& get_path_finder(void) const;
	Graph* get_graph(void);
};