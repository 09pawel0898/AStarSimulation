#include "pch.h"

#include "Enemy.h"
#include "Animation.h"
#include "PathFinder.h"
#include "Graph.h"

Enemy::Enemy(Context context, Graph* graph)
	:	mContext(&context),
		mGraph(graph)
{
	//mAnimation = new Animation()
	
	int x = rand() % mGraph->HEIGHT;
	int y = rand() % mGraph->WIDTH;
	mGridPosition = vec2i(x, y);
	mPathFinder = new PathFinder(*mGraph,mGridPosition);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*mPathFinder);
}

PathFinder& Enemy::get_path_finder(void) const
{
	return *mPathFinder;
}

Graph* Enemy::get_graph(void)
{
	return mGraph;
}
