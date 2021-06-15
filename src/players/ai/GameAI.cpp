#include "GameAI.h"
#include "../../components/board/GameBoard.h"
#include <vector>
#include <stack>
#include <numeric>
#include <unordered_map>
#include <assert.h>
#include <algorithm>
using namespace reversi;

namespace AIFunctions
{
	// based on minimax algorithm
	// near_bottom must be an odd number
	static int evaluate(const GameBoard& board, uint32_t depth, uint32_t max_depth, uint32_t turn)
	{
		if (depth == max_depth)
			return board.getPlacables().size();

		turn = (turn % 2) + 1;

		if (depth % 2)	// player's turn, g = max(l0, l1, ..., ln-1)
		{
			auto children = board.getPlacables();
			int max = 0;

			std::for_each(std::begin(children), std::end(children),
				[&](auto& disk)
				{
					//std::unique_ptr<GameBoard> child = std::make_unique<GameBoard>(b);
					GameBoard* child = new GameBoard(&board);
					child->put(turn, *disk.lock());
					max = std::max(max, evaluate(child, depth + 1, max_depth, turn));
					delete child;
				});
			return max;
		}
		else			// AI's turn, choose c = min(g0, g1, ..., gn-1)
		{
			auto children = board.getPlacables();
			int min = INT32_MAX;

			std::for_each(std::begin(children), std::end(children),
				[&](auto& disk)
				{
					//std::unique_ptr<GameBoard> child = std::make_unique<GameBoard>(b);
					GameBoard* child = new GameBoard(&board);
					child->put(turn, *disk.lock());
					min = std::min(min, evaluate(child, depth + 1, max_depth, turn));
					delete child;
				});
			return (min == INT32_MAX) ? 0 : min;
		}
	}
}
#include <iostream>
BoardPosition GameAI::makeDicision(const GameBoard& board)
{
	auto placables = board.getPlacables();
	int val, min = INT32_MAX;
	BoardPosition decision;

	std::for_each(std::begin(placables), std::end(placables),
		[&](std::weak_ptr<Stone>& disk)
		{
			GameBoard* candidate = new GameBoard(&board);
			candidate->put(static_cast<uint32_t>(type), *disk.lock());

			if (min > (val = think(*candidate)))
			{
				min = val;
				decision =
				{
					disk.lock()->getRow(),
					disk.lock()->getCol()
				};
			}
			delete candidate;
		});
	std::cout << decision.brow << ' ' << decision.bcol << std::endl;
	return decision;
}

// returns nsupcase, max_depth is always even number
// max_depth must be an even number or 0
int GameAI::think(const GameBoard& board, const uint32_t max_depth, const uint32_t aiType)
{
	assert(max_depth % 2);
	return AIFunctions::evaluate(board, 1, max_depth, aiType);
}
