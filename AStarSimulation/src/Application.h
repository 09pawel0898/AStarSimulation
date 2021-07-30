#pragma once

#include "./res/ResourceManager.h"
#include "./states/StateManager.h"

class Application : private sf::NonCopyable
{
public:
	static int WIDTH;
	static int HEIGHT;
	static int NUM_ENEMIES;
private:
	static const sf::Time TIME_PER_FRAME;

	sf::RenderWindow* mWindow;
	TextureManager mTextures;
	FontManager mFonts;
	States::StateManager* mStateManager;

private:
	sf::Text mFpsLabel;
	std::size_t FPS;

	void update_statistics(sf::Time elapsedTime);
	void register_states(void);

	void render(void);
	void process_events(void);
	void update_scene(sf::Time elapsedTime);

	void load_settings_from_file(void);
	void init_labels(void);

public:
	Application(void);
	void run(void);
};