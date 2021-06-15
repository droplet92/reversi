#pragma once
#include "../../types/Position.h"
#include "../../types/PlayerType.h"
#include "../../utilities/Timer.h"

namespace reversi
{
	class GameBoard;

	class GameAI
	{
	public:
		const PlayerType type;

	private:
		Timer timer;

	public:
		GameAI(const PlayerType type) :type(type) {}
		virtual ~GameAI() {}

		BoardPosition makeDicision(const GameBoard& board);

		virtual int think([[maybe_unused]] GameBoard& board) = 0;
		
		virtual void printDifficulty() const = 0;

	protected:
		int think(const GameBoard& board, const uint32_t max_depth, const uint32_t playerType);
	};
}