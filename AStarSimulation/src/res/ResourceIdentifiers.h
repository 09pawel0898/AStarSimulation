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
		// sprites
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
		OBDDOWNRIGHT,
		NODE,
		CONNECTION
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
