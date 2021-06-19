#include "pch.h"
#include "./SimulationState.h"

namespace States
{

	SimulationState::SimulationState(StateManager &stateManager, Context context) :
		State(stateManager, context),
		mExitToMenuState(false)
	{
		set_gui(context);
	}

	SimulationState::~SimulationState(void)
	{
	}

	void SimulationState::set_gui(Context& context)
	{
		//context.mTextures->load_resource(Textures::ID::B_READY, "assets/readybutton.png");

		//sf::Font &font = context.mFonts->get_resource(Fonts::ID::VIKING);
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
		//window->draw(mWorld);
		std::cout << "Hello from sim\n";
	}

	bool SimulationState::update_scene(sf::Time deltaTime)
	{


		return true;
	}

	bool SimulationState::handle_event(const sf::Event &event)
	{
		
		return true;
	}

}