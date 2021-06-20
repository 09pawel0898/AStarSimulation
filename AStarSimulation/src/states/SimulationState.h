#pragma once

#include "./State.h"
class World;

namespace States
{
	class SimulationState : public State
	{
	private:
		//GUI::WidgetContainer<Widgets> mWidgets;
		//std::unordered_map<Keys, bool> mKeysPressed;
		World* mWorld;
		void init_resources(Context& context);

	public:
		SimulationState(StateManager &stateManager, Context context);
		virtual ~SimulationState(void);

		virtual void render(void) override;
		virtual bool update_scene(sf::Time deltaTime) override;
		virtual bool handle_event(const sf::Event &event) override;
	};
}