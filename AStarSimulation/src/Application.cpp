#include "pch.h"
#include "./Application.h"
#include "./Utility.h"
#include "./states/State.h"
#include "./states/StateIdentifiers.h"
#include "./states/SimulationState.h"
#include "./res/ResourceIdentifiers.h"

const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);

Application::Application(void) :
	mWindow(sf::RenderWindow(sf::VideoMode(1280, 720), "Game", sf::Style::Titlebar | sf::Style::Close)),
	mTextures(),
	mFonts(),
	mStateManager(States::State::Context(mWindow, mTextures, mFonts)),
	mFpsLabel(),
	FPS(0)
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setFramerateLimit(100);

	mFonts.load_resource(Fonts::ID::SANSATION, "assets/fonts/Sansation.ttf");
	//mTextures.load_resource(Textures::ID::B_MENU1, "assets/button1.png");
	
	init_labels();
	register_states();

	mStateManager.add_state(States::ID::SIMULATION);
}

void Application::render(void)
{
	mWindow.clear();

	mStateManager.render();
	mWindow.draw(mFpsLabel);
	mWindow.display();
}

void Application::process_events(void)
{
	static sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateManager.handle_event(event);

		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
	}
}

void Application::update_scene(sf::Time deltaTime)
{
	mStateManager.update_scene(deltaTime);
}

void Application::update_statistics(sf::Time elapsedTime)
{
	static sf::Time mStatisticsUpdateTime = sf::seconds(0);

	mStatisticsUpdateTime += elapsedTime;
	FPS++;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mFpsLabel.setString("FPS = " + Utility::to_string(FPS) + "\n");
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		FPS = 0;
	}
}

void Application::register_states(void)
{
	mStateManager.register_state<States::SimulationState>(States::ID::SIMULATION);
}

void Application::run(void)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			process_events();
			update_scene(TIME_PER_FRAME);
			if (mStateManager.is_empty())
				mWindow.close();
		}

		update_statistics(elapsedTime);
		render();
	}
}

void Application::init_labels(void)
{
	mFpsLabel.setFont(mFonts.get_resource(Fonts::ID::SANSATION));
	mFpsLabel.setPosition(5.0f, 5.0f);
	mFpsLabel.setCharacterSize(10);
	mFpsLabel.setFillColor(sf::Color::White);
}