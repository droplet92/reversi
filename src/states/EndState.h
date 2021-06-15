#pragma once
#include "../GameState.h"
#include "../components/buttons/GameButton.h"

namespace reversi
{
	class EndState : public GameState
	{
	public:
		static const std::string REGAME_BUTTON_NAME;
		static const sf::Vector2f REGAME_BUTTON_POS;
		static const sf::IntRect REGAME_BUTTON_SIZE;
		static const uint32_t REGAME_BUTTON_ANIMATION_FRAME;
		static const uint8_t REGAME_BUTTON_ALPHA;

		static const std::string EXIT_BUTTON_NAME;
		static const sf::Vector2f EXIT_BUTTON_POS;
		static const sf::IntRect EXIT_BUTTON_SIZE;
		static const uint32_t EXIT_BUTTON_ANIMATION_FRAME;
		static const uint8_t EXIT_BUTTON_ALPHA;

	private:
		AnimationButton regameButton;
		AnimationButton exitButton;

	public:
		EndState(Game* game);
		~EndState() final {}

		void enter(Game& game) final;

		void update(Game&, InputManager& inputManager) final {}

		void nupdate(const MouseInput& mouseInput) final;

	private:
		void exit(Game& game) final;
	};
}