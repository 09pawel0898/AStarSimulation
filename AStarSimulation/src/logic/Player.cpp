#include "pch.h"
#include "./Player.h"

Player::Player()
{
	init_textures();

	/* camera */

	mPlayerCamera.setSize(640, 360);
	mPlayerCamera.setCenter(300, 300);
}

Player::~Player()
{
}

void Player::init_textures(void)
{
	//mTextures.load_resource(Textures::ID::CAR1		, "./assets/img/car.png");
}

bool Player::move(const std::unordered_map<Keys, bool>& keysPressed, const sf::Time& dt)
{
	bool isMoving = false;
	return true;
}

void Player::update_scene(const sf::Time& dt, const std::unordered_map<Keys, bool>& keysPressed)
{
	move(keysPressed, dt);
	
	// update animation
	//mCurrentAnim = mAnims.find(mCurrentAnimID);
	// update camera

}



void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

sf::View& Player::get_camera(void)
{
	return mPlayerCamera;
}

vec2f Player::get_world_pos(void)
{
	return vec2f();
}
