#include "pch.h"
#include "World.h"
#include "../res/ResourceManager.h"
#include "Graph.h"
#include "PathFinder.h"
#include "Enemy.h"

World::World(uint8_t width, uint8_t height, uint8_t numEnemies, Context context)
	:	WIDTH(width),
		HEIGHT(height),
		mNumEnemies(numEnemies),
		mContext(context)
{
	init_enemies(context);
}

void World::init_world(void)
{
	Tile temp;
	temp.rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::GRASS));
	temp.rec.setSize(vec2f(64, 64));
	temp.tileType = TileType::GRASS;

	for (int i = 0; i < HEIGHT; i++)
	{
		mGridTiles.emplace_back(std::vector<Tile>());
		for (int j = 0; j < WIDTH; j++)
		{
			temp.rec.setPosition(vec2f((float)(j * 64), (float)(i * 64)));
			mGridTiles[i].emplace_back(temp);
		}
	}
}

void World::init_enemies(Context context)
{
	for (int i = 0; i < mNumEnemies; i++)
	{
		Graph* graph = new Graph(WIDTH, HEIGHT);
		mEnemies.push_back(Enemy(context, graph));
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
	for (auto& enemy : mEnemies)
	{
		target.draw(enemy.get_path_finder());
	}
}

bool World::switch_tile_state(const vec2i& mousePos)
{
	vec2i coord = vec2i(mousePos.y / 64, mousePos.x / 64);

	/*
	if (mGridTiles[coord.x][coord.y].type == TileType::GRASS)
		switch_tile_to_obstacle(coord);
	else if(mGridTiles[coord.x][coord.y].type == TileType::OBSTACLE)
		switch_tile_to_grass(coord);
	*/
	update_grid_tiles(coord);

	for (auto& enemy : mEnemies)
	{
		enemy.mGraph->update_graph(coord);
		enemy.get_path_finder().solve_AStar();
	}
	
	return true;
}

bool World::switch_path_finding_type(void) const
{
	for (auto& enemy : mEnemies)
	{
		enemy.get_path_finder().change_path_type();
		enemy.get_path_finder().solve_AStar();
	}
	return true;
}

void World::change_path_visibility(void) const
{
	for (auto& enemy : mEnemies)
	{
		if (enemy.get_path_finder().get_visibility())
			enemy.get_path_finder().hide_path();
		else
			enemy.get_path_finder().show_path();
	}
}

/*
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
*/

bool World::update_grid_tiles(const vec2i& coord)
{
	if (mGridTiles[coord.x][coord.y].tileType == TileType::OBS)
	{
		mGridTiles[coord.x][coord.y].tileType = TileType::GRASS;
		mGridTiles[coord.x][coord.y].rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::GRASS));
		return true;
	}
	else if (mGridTiles[coord.x][coord.y].tileType == TileType::GRASS)
		mGridTiles[coord.x][coord.y].tileType = TileType::OBS;


	for (int x = 0; x < HEIGHT; x++)
	{
		for (int y = 0; y < WIDTH; y++)
		{
			bool dirs[4] = { false }; // UP/DOWN/LEFT/RIGHT
			if (x - 1 >= 0)
			{
				if (mGridTiles[x - 1][y].tileType == TileType::OBS)
					dirs[0] = true;
			}
			if (x + 1 < HEIGHT)
			{
				if (mGridTiles[x + 1][y].tileType == TileType::OBS)
					dirs[1] = true;
			}
			if (y - 1 >= 0)
			{
				if (mGridTiles[x][y - 1].tileType == TileType::OBS)
					dirs[2] = true;
			}
			if (y + 1 < WIDTH)
			{
				if (mGridTiles[x][y + 1].tileType == TileType::OBS)
					dirs[3] = true;
			}

			ConnectionType prev = mGridTiles[coord.x][coord.y].connectionType;

			if (dirs[0] && dirs[1] && dirs[2] && dirs[3])
				mGridTiles[coord.x][coord.y].connectionType = ConnectionType::CROSS;
			else if (dirs[0] && dirs[1])
				mGridTiles[coord.x][coord.y].connectionType = ConnectionType::UPDOWN;
			else if (dirs[2] && dirs[3])
				mGridTiles[coord.x][coord.y].connectionType = ConnectionType::LEFTRIGHT;
			else if (dirs[0])
				mGridTiles[coord.x][coord.y].connectionType = ConnectionType::UP;
			else if (dirs[1])
				mGridTiles[coord.x][coord.y].connectionType = ConnectionType::DOWN;
			else if (dirs[2])
				mGridTiles[coord.x][coord.y].connectionType = ConnectionType::LEFT;
			else if (dirs[3])
				mGridTiles[coord.x][coord.y].connectionType = ConnectionType::RIGHT;

			if (mGridTiles[coord.x][coord.y].connectionType != prev)
			{
				switch (mGridTiles[coord.x][coord.y].connectionType)
				{
					case ConnectionType::CROSS:		mGridTiles[coord.x][coord.y].rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::OBSCROSS));		break;
					case ConnectionType::UPDOWN:	mGridTiles[coord.x][coord.y].rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::OBSUPDOWN));	break;
					case ConnectionType::LEFTRIGHT:	mGridTiles[coord.x][coord.y].rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::OBSLEFTRIGHT));	break;
					case ConnectionType::UP:		mGridTiles[coord.x][coord.y].rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::OBSUP));		break;
					case ConnectionType::DOWN:		mGridTiles[coord.x][coord.y].rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::OBSDOWN));		break;
					case ConnectionType::LEFT:		mGridTiles[coord.x][coord.y].rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::OBSLEFT));		break;
					case ConnectionType::RIGHT:		mGridTiles[coord.x][coord.y].rec.setTexture(&mContext.mTextures->get_resource(Textures::ID::OBSRIGHT));		break;
				}
			}
		}
	}
}


void World::update_ending_point(const vec2i& coord) const
{
	Node* temp = &mEnemies.front().mGraph->get_nodes()[coord.x * WIDTH + coord.y];

	if (temp->obstacle == false)
	{
		for (auto& enemy : mEnemies)
		{
			enemy.get_path_finder().set_end(&enemy.mGraph->get_nodes()[coord.x * WIDTH + coord.y]);
			enemy.get_path_finder().solve_AStar();
		}
	}
}


