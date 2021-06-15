#pragma once
#include "ai/GameAI.h"
#include "../GamePlayer.h"
#include <future>
#include <SFML/Graphics.hpp>

namespace reversi
{
	class AIPlayer : public GamePlayer
	{
	public:
		static const std::string LOADING_IMAGE;
		static const sf::Vector2f BLACK_LOADING_POS;
		static const sf::Vector2f WHITE_LOADING_POS;
		static const sf::IntRect LOADING_SIZE;
		static const uint32_t LOADING_FRAME;
		static const uint8_t LOADING_ALPHA;

	private:
		GameAI* ai;
		std::future<BoardPosition>* future;

	public:
		AIPlayer(const PlayerType type, GameAI* ai);
		~AIPlayer() final;

		void changeAI(GameAI* _ai)
		{
			delete ai;
			ai = _ai;
			ai->printDifficulty();
		}

		void init();

		Decision awaitDecision(GameBoard& board, const MouseInput&) final;
	};
}