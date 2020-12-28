#pragma once
#include "GameState.h"
#include "components/board/GameBoard.h"
#include "components/board/GameBoardFooter.h"
#include "components/mouse/Mouse.h"
#include "managers/AnimationManager.h"
#include "managers/PlayerManager.h"
#include "managers/InputManager.h"
#include "utilities/Jukebox.h"

namespace yothello
{
	class Game
	{
	public:
		static const sf::Vector2u WINDOW_SIZE;
		static const std::string WINDOW_TITLE;

	private:
		GameState* state;

		sf::RenderWindow window;
		Jukebox bgm;
		Mouse mouse;

		GameBoard board;
		GameBoardFooter footer;
		InputManager inputManager;
		AnimationManager animationManager;
		PlayerManager playerManager;

	public:
		Game();
		~Game();

		bool over() const { return board.isOver(); }

		GameBoard& getBoard() { return board; }
		GameBoardFooter& getFooter() { return footer; }
		AnimationManager& getAnimationManager() { return animationManager; }
		PlayerManager& getPlayerManager() { return playerManager; }

		void changeState(GameState* _state);
		void run();

	private:
		void processInput(sf::Event& event);
		void update(const float dt);
		void render();
	};
}