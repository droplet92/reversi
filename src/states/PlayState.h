#pragma once
#include "../GameState.h"
#include "../animations/GameAnimation.h"

namespace yothello
{
	class PlayState : public GameState
	{
	private:
		GameAnimation _pass;

	public:
		PlayState(Game* game);
		~PlayState() final {}

		void enter(Game&) final {}

		void update(Game& game, InputManager& inputManager) final;

		void nupdate(const MouseInput& mouseInput) final;

	private:
		void exit(Game& game) final;
	};
}