#pragma once
#include "../GameState.h"
#include "../animations/GameAnimation.h"

namespace reversi
{
	class TitleState : public GameState
	{
	private:
		GameAnimation _game_title;

	public:
		TitleState(Game* game);
		~TitleState() final {}

		void enter(Game& game) final;

		void update(Game&, InputManager& inputManager) final {};

		void nupdate(const MouseInput& mouseInput) final;

	private:
		void exit(Game& game) final;
	};
}