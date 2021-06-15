#pragma once
#include "../GameState.h"
#include "../components/buttons/GameButton.h"

namespace reversi
{
	class SelectState : public GameState
	{
	public:
		static const std::string SELECT_BLACK_BUTTON_NAME;
		static const std::string SELECT_WHITE_BUTTON_NAME;
		static const sf::Vector2f SELECT_BLACK_BUTTON_POS;
		static const sf::Vector2f SELECT_WHITE_BUTTON_POS;

	private:
		PlainButton select_black;
		PlainButton select_white;

	public:
		SelectState(Game* game);
		~SelectState() final {}

		void enter(Game& game) final;

		void update(Game&, InputManager& inputManager) final {};

		void nupdate(const MouseInput& mouseInput) final;

	private:
		void exit(Game& game) final;
	};
}