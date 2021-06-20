#include "pch.h"
#include "./SimulationState.h"
#include "../res/ResourceManager.h"
#include "../Application.h"
#include "../logic/World.h"

namespace States
{

	SimulationState::SimulationState(StateManager &stateManager, Context context) :
		State(stateManager, context),
		mWorld(new World(Application::WIDTH,Application::HEIGHT, Application::NUM_ENEMIES,context))
	{
		init_resources(context);
		mWorld->init_world();
	}

	SimulationState::~SimulationState(void)
	{
	}

	void SimulationState::init_resources(Context& context)
	{
		context.mTextures->load_resource(Textures::ID::GRASS, "assets/img/grass.png");
		context.mTextures->load_resource(Textures::ID::OBSTACLE, "assets/img/obstacle.png");
		context.mTextures->load_resource(Textures::ID::NODE, "assets/img/node.png");
		context.mTextures->load_resource(Textures::ID::CONNECTION, "assets/img/connection.png");

		//spr.setTexture(context.mTextures->get_resource(Textures::ID::GRASS));


		//sf::Texture &texture = context.mTextures->get_resource(Textures::ID::B_READY);

		//mWidgets.insert_widget<GUI::Button>(Widgets::B_READY, new GUI::Button(sf::Vector2f(90.0f, 730.f), texture, "Ready", font, 25));
		//mWidgets.get_widget<GUI::Button>(Widgets::B_READY)->set_text_color(sf::Color::White);

		
		/*
		mWidgets.get_widget<GUI::Button>(Widgets::B_LEAVE)->set_callback([this](void)
		{
			disconnect();
		});

		*/
		
	}

	void SimulationState::render(void)
	{
		static sf::RenderWindow* window = get_context().mWindow;
		//window->draw(spr);
		window->draw(*mWorld);

		// if drawing graph active
		mWorld->draw_graph();
		
	}

	bool SimulationState::update_scene(sf::Time deltaTime)
	{


		return true;
	}

	bool SimulationState::handle_event(const sf::Event &event)
	{
		static bool enable = true;
		vec2i mousePos = sf::Mouse::getPosition(*get_context().mWindow);

		if (event.type == sf::Event::MouseButtonReleased)
		{
			mWorld->try_add_obstacle(mousePos);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			enable = false;
			switch (event.key.code)
			{
				case sf::Keyboard::Space: 
					mWorld->change_graph_visibility();
					break;
			}
		}
		else if (event.type == sf::Event::KeyReleased)
			enable = true;

		return true;
	}

}