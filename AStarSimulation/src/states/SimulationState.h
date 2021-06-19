#pragma once

#include "./State.h"

namespace States
{
	class SimulationState : public State
	{
	private:


	private:
		//GUI::WidgetContainer<Widgets> mWidgets;
		//std::unordered_map<Keys, bool> mKeysPressed;
		//World mWorld;

		void set_gui(Context& context);

	public:
		bool mExitToMenuState;

		SimulationState(StateManager &stateManager, Context context);
		virtual ~SimulationState(void);

		virtual void render(void) override;
		virtual bool update_scene(sf::Time deltaTime) override;
		virtual bool handle_event(const sf::Event &event) override;
	};
}