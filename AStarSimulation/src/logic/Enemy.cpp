#include "pch.h"

#include "Enemy.h"
#include "Animation.h"
#include "../Utility.h"
#include "Graph.h"
#include "../res/ResourceManager.h"


Enemy::Enemy(Context context, Graph* graph, std::list<vec2i>& coordsTakenByEnemies)
	: mContext(&context),
	mGraph(graph),
	mPathExist(true),
	mPause(true)
{
	init_random_position(coordsTakenByEnemies);
	init_components();
	init_animations();
	init_directions();
}

void Enemy::init_random_position(std::list<vec2i>& coordsTakenByEnemies)
{
	std::list<vec2i>::iterator element;
	vec2i randomPos;

	do
	{
		randomPos.x = rand() % (mGraph->HEIGHT - 2 + 1) + 1;
		randomPos.y = rand() % (mGraph->WIDTH - 2 + 1) + 1;
		element = std::find(coordsTakenByEnemies.begin(), coordsTakenByEnemies.end(), vec2i(randomPos.x, randomPos.y));
	} while (element != coordsTakenByEnemies.end());
	mGridPosition = vec2i(randomPos.x, randomPos.y);
}

void Enemy::init_components(void)
{
	mSpeed = 1.0 + (double)((rand() % 9 + 1)) / 10;
	mPosition = { (float)(mGridPosition.y * 64 + 32),(float)(mGridPosition.x * 64 + 32) };
	mPathFinder = new PathFinder(*mGraph, mGridPosition, mPathExist);
}

void Enemy::init_animations(void)
{
	mAnims.emplace(std::make_pair(AnimID::IDLE, Animation(mContext->mTextures->get_resource(Textures::ID::ENEMYIDLE), vec2i(64, 64), 1, sf::seconds(0.6f), true)));
	mAnims.emplace(std::make_pair(AnimID::WALK, Animation(mContext->mTextures->get_resource(Textures::ID::ENEMYWALK), vec2i(64, 64), 2, sf::seconds(0.6f), true)));
	mCurrentAnimID = AnimID::IDLE;
	mCurrentAnim = mAnims.find(mCurrentAnimID);
}

void Enemy::init_directions(void)
{
	mDirections.emplace(std::make_pair(Direction::RD, vec2f(64, 64)));
	mDirections.emplace(std::make_pair(Direction::LD, vec2f(64, -64)));
	mDirections.emplace(std::make_pair(Direction::RU, vec2f(-64, 64)));
	mDirections.emplace(std::make_pair(Direction::LU, vec2f(-64, -64)));
	mDirections.emplace(std::make_pair(Direction::U, vec2f(-64, 0)));
	mDirections.emplace(std::make_pair(Direction::D, vec2f(64, 0)));
	mDirections.emplace(std::make_pair(Direction::L, vec2f(0, -64)));
	mDirections.emplace(std::make_pair(Direction::R, vec2f(0, 64)));
}

bool Enemy::set_anim(AnimID newAnim)
{
	if (mCurrentAnimID != newAnim)
	{
		mCurrentAnimID = newAnim;
		mCurrentAnim = mAnims.find(mCurrentAnimID);
		return true;
	}
	return false;
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
		move(dt);
	}
	else if (mPathExist)
	{
		update_rotation();
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

vec2i Enemy::update_grid_position(void)
{
	mGridPosition = { (int)(mPosition.y / 64) , (int)(mPosition.x / 64) };
	return mGridPosition;
}

bool Enemy::move(const sf::Time& dt)
{
	auto distance = [](const vec2f& a, const vec2f& b)
	{
		return sqrtf((float)((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
	};

	Node* end = mPathFinder->get_end();

	vec2i nextGridCoord = { (int)(mGridPosition.x + mDirections[mCurrentDir].x / 64),(int)(mGridPosition.y + mDirections[mCurrentDir].y / 64) };
	float dist = distance(mPosition, vec2f((float)(nextGridCoord.y * 64 + 32), (float)(nextGridCoord.x * 64 + 32)));

	if (dist > 1.0f)
	{
		set_anim(AnimID::WALK);
		// generate vector pointng to the next grid position
		vec2f dirVec = vec2f((float)(nextGridCoord.y * 64 + 32) - mPosition.x, (float)(nextGridCoord.x * 64 + 32) - mPosition.y);
		Utility::normalise_vec(dirVec);
		
		// move enemy a bit
		mPosition.x += (float)(dirVec.x * mSpeed);
		mPosition.y += (float)(dirVec.y * mSpeed);
	}
	else 
	{
		 if (end->x == mGridPosition.y && end->y == mGridPosition.x)
		 {
			 set_anim(AnimID::IDLE);
		 }
		// if enemy rached the next grid coord, update A* and set its new grid coord
		mGridPosition = nextGridCoord;
		mPathFinder->set_start(&mGraph->get_nodes()[mGridPosition.x * mGraph->WIDTH + mGridPosition.y]);
		mPathFinder->solve_AStar();
	}
	return true;
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
