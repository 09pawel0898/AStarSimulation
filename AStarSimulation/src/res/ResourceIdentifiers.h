#pragma once

#include <cstdint>

namespace sf
{
	class Texture;
	class Font;
}

class Animation;

namespace Textures
{
	enum class ID : uint8_t
	{
		GRASS,
		OBS,
		OBSLEFTRIGHT,
		OBSUPDOWN,
		OBSRIGHT,
		OBSDOWN,
		OBSLEFT,
		OBSUP,
		OBSCROSS,
		OBSUPLEFT,
		OBSUPRIGHT,
		OBSDOWNLEFT,
		OBSDOWNRIGHT,
		OBSTRILEFT,
		OBSTRIRIGHT,
		OBSTRIUP,
		OBSTRIDOWN,
		NODE,
		CONNECTION,

		ENEMYWALK,
		ENEMYIDLE
	};
}

namespace Fonts
{
	enum class ID : uint8_t
	{
		SANSATION
	};
}

template <typename Type, typename ID>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::ID> TextureManager;
typedef ResourceManager<sf::Font, Fonts::ID> FontManager;
