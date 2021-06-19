#pragma once

#include "../states/State.h"

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
	uint8_t mWidth;
	uint8_t mHeight;
	uint8_t mNumEnemies;
	States::State::Context mContext;

	std::vector<std::vector<Tile>> mGridTiles;
	
	void init_border_obstacles(void);	
public:
	void init_world(void);

	World(uint8_t width, uint8_t height, uint8_t numEnemies, States::State::Context context);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void try_add_obstacle(const vec2i& mousePos);


private:

	void switch_tile_to_grass(const vec2i& coord);
	void switch_tile_to_obstacle(const vec2i& coord);

};