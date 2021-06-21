#include "pch.h"

#include "Enemy.h"
#include "Animation.h"

#include "Graph.h"
#include "../res/ResourceManager.h"


Enemy::Enemy(Context context, Graph* graph, std::list<vec2i>& coordsTakenByEnemies)
	:	mContext(&context),
		mGraph(graph),
		mPathExist(true),
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
	mCoordsTakenOnTheGrid.push_back(randomPos);

	mGridPosition = vec2i(randomPos.x, randomPos.y);
	mPosition = { (float)(mGridPosition.y * 64 + 32),(float)(mGridPosition.x * 64 + 32) };
	mPathFinder = new PathFinder(*mGraph,mGridPosition, mPathExist);

	init_animations();
	init_directions();
}

void Enemy::init_animations(void)
{
	mAnims.emplace(std::make_pair(AnimID::IDLE, Animation(mContext->mTextures->get_resource(Textures::ID::ENEMYIDLE), vec2i(64, 64), 1, sf::seconds(0.5f), true)));
	mAnims.emplace(std::make_pair(AnimID::WALK, Animation(mContext->mTextures->get_resource(Textures::ID::ENEMYWALK), vec2i(64, 64), 2, sf::seconds(0.5f), true)));

	mCurrentAnimID = AnimID::IDLE;
	mCurrentAnim = mAnims.find(mCurrentAnimID);
}

void Enemy::init_directions(void)
{
	mDirections.emplace(std::make_pair(Direction::RD, vec2f(64, 64)));
	mDirections.emplace(std::make_pair(Direction::LD, vec2f(-64, 64)));
	mDirections.emplace(std::make_pair(Direction::RU, vec2f(64, -64)));
	mDirections.emplace(std::make_pair(Direction::LU, vec2f(-64, -64)));
	mDirections.emplace(std::make_pair(Direction::U, vec2f(0, -64)));
	mDirections.emplace(std::make_pair(Direction::D, vec2f(0, 64)));
	mDirections.emplace(std::make_pair(Direction::L, vec2f(-64, 0)));
	mDirections.emplace(std::make_pair(Direction::R, vec2f(64, 0)));
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*mPathFinder);
	mCurrentAnim->second.draw(target, states);
}

void Enemy::update(const sf::Time& dt)
{
	if (!mPause && mPathExist)
	{
		update_rotation();
		//move(dt);
	}
	mCurrentAnim = mAnims.find(mCurrentAnimID);
	mCurrentAnim->second.update_scene(dt, mPosition);
}

void Enemy::update_rotation(void)
{
	Direction dir = mPathFinder->get_direction();
	float degrees = 0.f;

	switch (dir)
	{
		case Direction::RD: degrees = 135.f; break;
		case Direction::LD: degrees = 225.f; break;
		case Direction::RU: degrees = 45.f; break;
		case Direction::LU: degrees = 315.f; break;
		case Direction::U: degrees = 0.f; break;
		case Direction::D: degrees = 180.f; break;
		case Direction::L: degrees = 270.f; break;
		case Direction::R: degrees = 90.f; break;
	}
	mCurrentDir = dir;
	mCurrentAnim->second.rotate(degrees);
}

bool Enemy::move(const sf::Time& dt)
{
	// If the next grid field on track is free then i perform a move
	//Direction dir = mCurrentDir;
	float a = mDirections[mCurrentDir].x;
	float b= mDirections[mCurrentDir].y;

	auto distance = [](Node* a, Node* b)
	{
		return sqrtf((float)((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y)));
	};

	vec2i nextGridCoord = { (int)(mGridPosition.x + mDirections[mCurrentDir].y/64),(int)(mGridPosition.y + mDirections[mCurrentDir].x/64) };
	std::list<vec2i>::iterator element = std::find(mCoordsTakenOnTheGrid.begin(), mCoordsTakenOnTheGrid.end(), vec2i(nextGridCoord.x, nextGridCoord.y));

	if (element == mCoordsTakenOnTheGrid.end())
	{

		mPosition.x += mDirections[mCurrentDir].x/63;
		mPosition.y += mDirections[mCurrentDir].y/63;

		//int c = mPosition.y / 64;
		int cc = mPosition.y / 64 - nextGridCoord.x;
		//int d = mPosition.x / 64;
		int dd = mPosition.x/ 64 - nextGridCoord.y;

		if (cc <0.001 && dd < 0.001)
		{
			mGridPosition = nextGridCoord;
			mPathFinder->set_start(&mGraph->get_nodes()[mGridPosition.x * mGraph->WIDTH + mGridPosition.y]);
			mPathFinder->solve_AStar();
		}
		return true;
	}
	else
		return false;
}

void Enemy::switch_pause(void)
{
	mPause = (mPause) ? false : true;
}

PathFinder& Enemy::get_path_finder(void) const
{
	return *mPathFinder;
}

Graph* Enemy::get_graph(void)
{
	return mGraph;
}
