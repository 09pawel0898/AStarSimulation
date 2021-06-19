#include "pch.h"
#include "World.h"
#include "../res/ResourceManager.h"

World::World(uint8_t width, uint8_t height, uint8_t numEnemies, States::State::Context context)
	:	mWidth(width),
		mHeight(height),
		mNumEnemies(numEnemies),
		mContext(context)
{
}

void World::init_world(void)
{
	Tile temp;
	temp.rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::GRASS));
	temp.rec.setSize(vec2f(64, 64));
	temp.type = TileType::GRASS;

	for (int i = 0; i < mHeight; i++)
	{
		mGridTiles.emplace_back(std::vector<Tile>());
		for (int j = 0; j < mWidth; j++)
		{
			temp.rec.setPosition(vec2f((float)(j * 64), (float)(i * 64)));
			mGridTiles[i].emplace_back(temp);
		}
	}
	init_border_obstacles();
}

void World::init_border_obstacles(void)
{
	bool obstacle;
	for (int i = 0; i < mHeight; i++)
	{
		obstacle = false;
		for (int j = 0; j < mWidth; j++)
		{
			if ((i == 0 || i == mHeight - 1) || (j == 0 || j == mWidth - 1))
			{
				mGridTiles[i][j].rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::OBSTACLE));
				mGridTiles[i][j].type = TileType::OBSTACLE;
			}
		}
	}
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < mHeight; i++)
	{
		for (int j = 0; j < mWidth; j++)
		{
			target.draw(mGridTiles[i][j].rec);
		}
	}
}

void World::try_add_obstacle(const vec2i& mousePos)
{
	vec2i coord = vec2i(mousePos.y / 64, mousePos.x / 64);
	if (mGridTiles[coord.x][coord.y].type == TileType::GRASS)
		switch_tile_to_obstacle(coord);
	else
		switch_tile_to_grass(coord);
}

void World::switch_tile_to_grass(const vec2i& coord)
{
	mGridTiles[coord.x][coord.y].rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::GRASS));
	mGridTiles[coord.x][coord.y].type = TileType::GRASS;
	//updateGraph();
}

void World::switch_tile_to_obstacle(const vec2i& coord)
{
	mGridTiles[coord.x][coord.y].rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::OBSTACLE));
	mGridTiles[coord.x][coord.y].type = TileType::OBSTACLE;
	//updateGraph();
}

