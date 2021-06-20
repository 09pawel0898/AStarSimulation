#pragma once

#include "../states/State.h"

class Graph;
class PathFinder;
typedef States::State::Context Context;

enum class TileType : uint8_t
{
	GRASS,
	OBSTACLE
};

struct Tile
{
	sf::RectangleShape rec;
	TileType type;
};

class World : public sf::Drawable
{
private:
	uint8_t WIDTH;
	uint8_t HEIGHT;
	uint8_t mNumEnemies;
	Context mContext;	
	Graph* mGraph;
	PathFinder* mPathFinder;
	
	std::vector<std::vector<Tile>> mGridTiles;
	
	void init_border_obstacles(void);	
public:
	void init_world(void);

	World(uint8_t width, uint8_t height, uint8_t numEnemies, Context context);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool switch_tile_state(const vec2i& mousePos);
	bool switch_path_finding_type(void) const;
	void change_path_visibility(void) const;
	void update_ending_point(const vec2i& coord) const;
private:

	void switch_tile_to_grass(const vec2i& coord);
	void switch_tile_to_obstacle(const vec2i& coord);
	
};