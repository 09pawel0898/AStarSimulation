#include "pch.h"

#include "World.h"
#include "../res/ResourceManager.h"
#include "Graph.h"
#include "PathFinder.h"

World::World(uint8_t width, uint8_t height, uint8_t numEnemies, Context context)
	:	WIDTH(width),
		HEIGHT(height),
		mNumEnemies(numEnemies),
		mContext(context)
{
	mGraph = new Graph(WIDTH, HEIGHT, mContext);
	mPathFinder = new PathFinder(mGraph);
}

void World::init_world(void)
{
	Tile temp;
	temp.rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::GRASS));
	temp.rec.setSize(vec2f(64, 64));
	temp.type = TileType::GRASS;

	for (int i = 0; i < HEIGHT; i++)
	{
		mGridTiles.emplace_back(std::vector<Tile>());
		for (int j = 0; j < WIDTH; j++)
		{
			temp.rec.setPosition(vec2f((float)(j * 64), (float)(i * 64)));
			mGridTiles[i].emplace_back(temp);
		}
	}
	//init_border_obstacles();
}

void World::init_border_obstacles(void)
{
	bool obstacle;
	for (int i = 0; i < HEIGHT; i++)
	{
		obstacle = false;
		for (int j = 0; j < WIDTH; j++)
		{
			if ((i == 0 || i == HEIGHT - 1) || (j == 0 || j == WIDTH - 1))
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
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			target.draw(mGridTiles[i][j].rec);
		}
	}
	target.draw(*mPathFinder);
}

bool World::switch_tile_state(const vec2i& mousePos)
{
	vec2i coord = vec2i(mousePos.y / 64, mousePos.x / 64);
	if (mGridTiles[coord.x][coord.y].type == TileType::GRASS)
		switch_tile_to_obstacle(coord);
	else if(mGridTiles[coord.x][coord.y].type == TileType::OBSTACLE)
		switch_tile_to_grass(coord);

	mGraph->update_graph(coord);
	mPathFinder->solve_AStar();
	return true;
}

bool World::switch_path_finding_type(void) const
{
	mPathFinder->change_path_type();
	mPathFinder->solve_AStar();
	return true;
}

void World::change_path_visibility(void) const
{
	if (mPathFinder->get_visibility())
		mPathFinder->hide_path();
	else
		mPathFinder->show_path();
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

void World::update_ending_point(const vec2i& coord) const
{
	Node* temp = &mGraph->get_nodes()[coord.x * WIDTH + coord.y];

	if (temp->obstacle == false)
	{
		mPathFinder->set_end(&mGraph->get_nodes()[coord.x * WIDTH + coord.y]);
		mPathFinder->solve_AStar();
	}
}

