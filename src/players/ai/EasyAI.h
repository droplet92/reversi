#pragma once
#include "GameAI.h"
#include "../../components/board/GameBoard.h"
#include "../../utilities/Logger.h"
#include <vector>

namespace reversi
{
	class EasyAI : public GameAI
	{
	public:
		EasyAI(const PlayerType type) :GameAI(type) {}

		int think([[maybe_unused]] GameBoard&) final { return 1; }

		void printDifficulty() const final { Logger::instance().write("EasyAI"); }
	};
}