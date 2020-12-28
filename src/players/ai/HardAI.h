#pragma once
#include "GameAI.h"
#include "../../components/board/GameBoard.h"
#include "../../utilities/Logger.h"
#include <stack>

namespace yothello
{
	class HardAI : public GameAI
	{
	public:
		HardAI(const PlayerType type) :GameAI(type) {}

		int think(GameBoard& board) final
		{
			static const uint32_t MAX_DEPTH = 15;
			return GameAI::think(&board, MAX_DEPTH, static_cast<uint32_t>(type));
		}

		void printDifficulty() const final { Logger::instance().write("HardAI"); }
	};
}