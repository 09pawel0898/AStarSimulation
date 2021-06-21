#include "pch.h"
#include "./SimulationState.h"
#include "../res/ResourceManager.h"
#include "../Application.h"
#include "../logic/World.h"
#include "../logic/Graph.h"

namespace States
{
	SimulationState::SimulationState(StateManager &stateManager, Context context) :
		State(stateManager, context)	
	{
		init_resources(context);
		mWorld = new World(Application::WIDTH, Application::HEIGHT, Application::NUM_ENEMIES, context);
		mWorld->init_world();
	}

	SimulationState::~SimulationState(void)
	{
	}

	void SimulationState::init_resources(Context& context)
	{
		context.mTextures->load_resource(Textures::ID::GRASS, "assets/img/grass.png");
		context.mTextures->load_resource(Textures::ID::OBS, "assets/img/obstacle.png");
		context.mTextures->load_resource(Textures::ID::NODE, "assets/img/node.png");
		context.mTextures->load_resource(Textures::ID::CONNECTION, "assets/img/connection.png");
		context.mTextures->load_resource(Textures::ID::OBSCROSS, "assets/img/obstacle9.png");
		context.mTextures->load_resource(Textures::ID::OBSDOWN, "assets/img/obstacle6.png");
		context.mTextures->load_resource(Textures::ID::OBSLEFT, "assets/img/obstacle7.png");
		context.mTextures->load_resource(Textures::ID::OBSRIGHT, "assets/img/obstacle5.png");
		context.mTextures->load_resource(Textures::ID::OBSUP, "assets/img/obstacle8.png");
		context.mTextures->load_resource(Textures::ID::OBSUPDOWN, "assets/img/obstacle4.png");
		context.mTextures->load_resource(Textures::ID::OBSLEFTRIGHT, "assets/img/obstacle3.png");
		context.mTextures->load_resource(Textures::ID::OBSDOWNLEFT, "assets/img/obstacle11.png");
		context.mTextures->load_resource(Textures::ID::OBSDOWNRIGHT, "assets/img/obstacle10.png");
		context.mTextures->load_resource(Textures::ID::OBSUPLEFT, "assets/img/obstacle12.png");
		context.mTextures->load_resource(Textures::ID::OBSUPRIGHT, "assets/img/obstacle13.png");
		context.mTextures->load_resource(Textures::ID::OBSTRIRIGHT, "assets/img/obstacle17.png");
		context.mTextures->load_resource(Textures::ID::OBSTRILEFT, "assets/img/obstacle15.png");
		context.mTextures->load_resource(Textures::ID::OBSTRIDOWN, "assets/img/obstacle14.png");
		context.mTextures->load_resource(Textures::ID::OBSTRIUP, "assets/img/obstacle16.png");

		context.mTextures->load_resource(Textures::ID::ENEMYWALK, "assets/img/enemy_walk.png");
		context.mTextures->load_resource(Textures::ID::ENEMYIDLE, "assets/img/enemy_idle.png");

		//spr.setTexture(context.mTextures->get_resource(Textures::ID::GRASS));


		//sf::Texture &texture = context.mTextures->get_resource(Textures::ID::B_READY);

		//mWidgets.insert_widget<GUI::Button>(Widgets::B_READY, new GUI::Button(sf::Vector2f(90.0f, 730.f), texture, "Ready", font, 25));
		//mWidgets.get_widget<GUI::Button>(Widgets::B_READY)->set_text_color(sf::Color::White);

		
		/*
		mWidgets.get_widget<GUI::Button>(Widgets::B_LEAVE)->set_callback([this](void)
		{
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

		mWorld->update_enemies(deltaTime);

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

		if (event.tileType == sf::Event::MouseButtonReleased)
		{
			mWorld->switch_tile_state(mMousePos);
		}
		else if (event.tileType == sf::Event::KeyPressed)
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
				case sf::Keyboard::LShift:
					mWorld->change_enemies_pause_state();
					break;
			}
		}
		else if (event.tileType == sf::Event::KeyReleased)
		{
			enable = true;
			mEndPointPositioning = false;
		}
		return true;
	}

}