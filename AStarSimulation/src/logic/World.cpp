#include "pch.h"

#include "World.h"
#include "../res/ResourceManager.h"
#include "Graph.h"

World::World(uint8_t width, uint8_t height, uint8_t numEnemies, Context context)
	:	mWidth(width),
		mHeight(height),
		mNumEnemies(numEnemies),
		mContext(context)
{
	mGraph = new Graph(mWidth, mHeight, mContext);
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
				mGraph->update_graph(vec2i(i, j));
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

bool World::try_add_obstacle(const vec2i& mousePos)
{
	vec2i coord = vec2i(mousePos.y / 64, mousePos.x / 64);
	if (mGridTiles[coord.x][coord.y].type == TileType::GRASS)
		switch_tile_to_obstacle(coord);
	else if(mGridTiles[coord.x][coord.y].type == TileType::OBSTACLE)
		switch_tile_to_grass(coord);
	mGraph->update_graph(coord);
	return true;
}

void World::draw_graph(void) const
{
	mContext.mWindow->draw(*mGraph);
}

void World::change_graph_visibility(void) const
{
	if (mGraph->get_visibility())
		mGraph->hide_graph();
	else
		mGraph->show_graph();
}

void World::switch_tile_to_grass(const vec2i& coord)
{
	mGridTiles[coord.x][coord.y].rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::GRASS));
	mGridTiles[coord.x][coord.y].type = TileType::GRASS;
}

void World::switch_tile_to_obstacle(const vec2i& coord)
{
	mGridTiles[coord.x][coord.y].rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::OBSTACLE));
	mGridTiles[coord.x][coord.y].type = TileType::OBSTACLE;
}

