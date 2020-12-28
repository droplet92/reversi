#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "managers/AnimationManager.h"
#include "managers/InputManager.h"
#include "inputs/MouseInput.h"
#include "utilities/Logger.h"	// added

namespace yothello
{
	class Game;

	class GameState : public GameObject
	{
	protected:
		Game* owner;

	public:
		GameState(Game* game);
		virtual ~GameState() {}

		virtual void enter([[maybe_unused]] Game& game) = 0;
		virtual void exit([[maybe_unused]] Game& game, InputManager& inputManager)
		{
			exit(game);
			inputManager.waitEvent();
		}

		virtual void update([[maybe_unused]] Game& game, InputManager& inputManager) = 0;
		virtual void nupdate(const MouseInput& mouseInput) = 0;

	private:
		virtual void exit([[maybe_unused]] Game& game) = 0;
	};
}