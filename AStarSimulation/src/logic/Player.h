#pragma once
#include "./Animation.h"
#include "../res/ResourceIdentifiers.h"
#include "../res/ResourceManager.h"

enum class Keys : uint8_t
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

enum class PlayerAction : uint8_t
{
	NUL,
	MOVE
};


class Player : public sf::Drawable
{
private:
	
	TextureManager mTextures;
	
	//AnimationManager mAnims;
	//std::unordered_map<PlayerAnim::ID, Animation> mAnims;
	//Animation* mCurrentAnim;

	//PlayerAnim::ID mCurrentAnimID;
	PlayerAction mCurrentAction;
	sf::View mPlayerCamera;

	void init_textures(void);
	bool move(const std::unordered_map<Keys, bool>& keysPressed, const sf::Time& dt);
public:
	Player();
	~Player();

	void update_scene(const sf::Time& dt, const std::unordered_map<Keys, bool>& keysPressed);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	vec2f get_world_pos(void);
};