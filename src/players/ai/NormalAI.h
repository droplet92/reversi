#pragma once
#include "GameAI.h"
#include "../../components/board/GameBoard.h"
#include "../../utilities/Logger.h"
#include <stack>

namespace reversi
{
	class NormalAI : public GameAI
	{
	public:
		NormalAI(const PlayerType type) :GameAI(type) {}

		int think(GameBoard& board) final
		{
			static const uint32_t MAX_DEPTH = 7;
			return GameAI::think(&board, MAX_DEPTH, static_cast<uint32_t>(type));
		}

		void printDifficulty() const final { Logger::instance().write("NormalAI"); }
	};
}