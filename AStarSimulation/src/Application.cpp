#include "pch.h"
#include "./Application.h"
#include "./Utility.h"
#include "./states/State.h"
#include "./states/StateIdentifiers.h"
#include "./states/SimulationState.h"
#include "./res/ResourceIdentifiers.h"
#include <istream>

const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);

int Application::HEIGHT;
int Application::WIDTH;
int Application::NUM_ENEMIES;

Application::Application(void) :
	
	mTextures(),
	mFonts(),
	
	mFpsLabel(),
	FPS(0)
{
	load_settings_from_file();
	mWindow = new sf::RenderWindow(sf::VideoMode(WIDTH*64, HEIGHT*64), "Game", sf::Style::Titlebar | sf::Style::Close);
	mStateManager = new States::StateManager(States::State::Context(mWindow, &mTextures, &mFonts));

	mWindow->setKeyRepeatEnabled(false);
	mWindow->setFramerateLimit(100);

	mFonts.load_resource(Fonts::ID::SANSATION, "assets/fonts/Sansation.ttf");
	//mTextures.load_resource(Textures::ID::GRASS, "assets/button1.png");
	
	init_labels();
	register_states();

	mStateManager->add_state(States::ID::SIMULATION);
}

void Application::render(void)
{
	mWindow->clear();

	mStateManager->render();
	mWindow->draw(mFpsLabel);
	mWindow->display();
}

void Application::process_events(void)
{
	static sf::Event event;
	while (mWindow->pollEvent(event))
	{
		mStateManager->handle_event(event);

		if (event.type == sf::Event::Closed)
		{
			mWindow->close();
		}
	}
}

void Application::update_scene(sf::Time deltaTime)
{
	mStateManager->update_scene(deltaTime);
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
	mStateManager->register_state<States::SimulationState>(States::ID::SIMULATION);
}

void Application::run(void)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow->isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			process_events();
			update_scene(TIME_PER_FRAME);
			if (mStateManager->is_empty())
				mWindow->close();
		}

		update_statistics(elapsedTime);
		render();
	}
}

void Application::load_settings_from_file(void)
{
	std::ifstream file;
	file.open("settings.txt");
	std::string line;
	if (file.good())
	{
		int i = 0;
		std::string label,value;
		std::stringstream ss;

		while (std::getline(file, line))
		{
			ss << line;
			ss >> label >> value;
			switch (i)
			{
				case 0:	WIDTH = atoi(value.c_str());		break;
				case 1:	HEIGHT = atoi(value.c_str());		break;
				case 2: NUM_ENEMIES = atoi(value.c_str());	break;
			}
			i++;
			ss.clear();
		}
		file.close();
	}
	else
	{
		perror("Error with reading setting from file");
	}
}

void Application::init_labels(void)
{
	mFpsLabel.setFont(mFonts.get_resource(Fonts::ID::SANSATION));
	mFpsLabel.setPosition(5.0f, 5.0f);
	mFpsLabel.setCharacterSize(10);
	mFpsLabel.setFillColor(sf::Color::White);
}