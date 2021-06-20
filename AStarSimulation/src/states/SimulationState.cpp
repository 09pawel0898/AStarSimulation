#include "pch.h"
#include "./SimulationState.h"
#include "../res/ResourceManager.h"
#include "../Application.h"
#include "../logic/World.h"
#include "../logic/Graph.h"

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
	}

	bool SimulationState::update_scene(sf::Time deltaTime)
	{	
		static vec2i prevPointedCoord = vec2i();

		mMousePos = sf::Mouse::getPosition(*get_context().mWindow);
		bool cursorInWindow = (mMousePos.x > 0 &&  mMousePos.x < Application::WIDTH*64 && mMousePos.y > 0 && mMousePos.y < Application::HEIGHT*64) ? true : false;

		if (mEndPointPositioning && cursorInWindow)
		{
			vec2i pointedCoord = vec2i(mMousePos.y / 64, mMousePos.x / 64);;
			if (prevPointedCoord != pointedCoord)
			{
				mWorld->update_ending_point(pointedCoord);
			}
			prevPointedCoord = pointedCoord;
		}
		return true;
	}

	bool SimulationState::handle_event(const sf::Event &event)
	{
		static bool enable = true;

		if (event.type == sf::Event::MouseButtonReleased)
		{
			mWorld->switch_tile_state(mMousePos);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			enable = false;
			switch (event.key.code)
			{
				case sf::Keyboard::Space: 
					mWorld->change_path_visibility();
					break;
				case sf::Keyboard::LControl:
					mWorld->switch_path_finding_type();
					break;
				case sf::Keyboard::LAlt:
					mEndPointPositioning = true;
					break;
			}
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			enable = true;
			mEndPointPositioning = false;
		}
		return true;
	}

}