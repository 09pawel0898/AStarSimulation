#include "pch.h"

#include "Enemy.h"
#include "Animation.h"
#include "PathFinder.h"
#include "Graph.h"
#include "../res/ResourceManager.h"

Enemy::Enemy(Context context, Graph* graph, std::list<vec2i>& coordsTakenByEnemies)
	:	mContext(&context),
		mGraph(graph),
		mPathExist(false),
		mPause(false),
		mCoordsTakenOnTheGrid(coordsTakenByEnemies)
{
	std::list<vec2i>::iterator element;
	vec2i randomPos;
	do
	{
		randomPos.x = rand() % (mGraph->HEIGHT - 2 + 1) + 1;
		randomPos.y = rand() % (mGraph->WIDTH - 2 + 1) + 1;
		element = std::find(mCoordsTakenOnTheGrid.begin(), mCoordsTakenOnTheGrid.end(), vec2i(randomPos.x, randomPos.y));
	} while (element != mCoordsTakenOnTheGrid.end());

	mGridPosition = vec2i(randomPos.x, randomPos.y);
	mPosition = { (float)(mGridPosition.y * 64 + 32),(float)(mGridPosition.x * 64 + 32) };
	mPathFinder = new PathFinder(*mGraph,mGridPosition);

	init_animations();
}

void Enemy::init_animations(void)
{
	mAnims.emplace(std::make_pair(AnimID::IDLE, Animation(mContext->mTextures->get_resource(Textures::ID::ENEMYIDLE), vec2i(64, 64), 1, sf::seconds(0.5f), true)));
	mAnims.emplace(std::make_pair(AnimID::WALK, Animation(mContext->mTextures->get_resource(Textures::ID::ENEMYWALK), vec2i(64, 64), 2, sf::seconds(0.5f), true)));

	mCurrentAnimID = AnimID::IDLE;
	mCurrentAnim = mAnims.find(mCurrentAnimID);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*mPathFinder);
	mCurrentAnim->second.draw(target, states);
}

void Enemy::update(const sf::Time& dt)
{
	mCurrentAnim = mAnims.find(mCurrentAnimID);
	mCurrentAnim->second.update_scene(dt, mPosition);
}

PathFinder& Enemy::get_path_finder(void) const
{
	return *mPathFinder;
}

Graph* Enemy::get_graph(void)
{
	return mGraph;
}
