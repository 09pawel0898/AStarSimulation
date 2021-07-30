#pragma once

#include "../states/State.h"

class Graph;
class PathFinder;
class Enemy;
typedef States::State::Context Context;

enum class ConnectionType : uint8_t
{
	DOWN,UP,LEFT,RIGHT,
	UPDOWN,LEFTRIGHT, DOWNLEFT, DOWNRIGHT, UPLEFT, UPRIGHT,
	CROSS,CENTER,
	TRILEFT,TRIRIGHT,TRIDOWN,TRIUP
};

enum class TileType : uint8_t
{
	GRASS,OBS
};

struct Tile
{
	sf::RectangleShape rec;
	TileType tileType;
	ConnectionType connectionType;
};

class World : public sf::Drawable
{
private:
	uint8_t WIDTH;
	uint8_t HEIGHT;
	uint8_t mNumEnemies;

	Context mContext;	
	std::list<Enemy> mEnemies;
	std::vector<std::vector<Tile>> mGridTiles;
	std::list<vec2i> mCoordsTakenByEnemies;

private:
	void init_enemies(Context context);

public:
	void init_world(void);

	World(uint8_t width, uint8_t height, uint8_t numEnemies, Context context);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool switch_tile_state(const vec2i& mousePos);
	bool switch_path_finding_type(void) const;
	void change_path_visibility(void) const;
	void change_enemies_pause_state(void);
	void update_ending_point(const vec2i& coord);
	void update_enemies(const sf::Time& dt);

private:
	bool update_grid_tiles(const vec2i& coord);
};