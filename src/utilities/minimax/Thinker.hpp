#pragma once
#include <stack>
#include <queue>
#include "Board.hpp"
#include "Stone.hpp"

template <size_t ROW, size_t COL>
class Thinker
{
public:
	using MinimaxBoard = Board<ROW, COL>;

private:
	std::stack<MinimaxBoard*> history;

public:
	Thinker() {}

	// returns nsupcase, max_depth is always odd number (except max board depth)
	int think(MinimaxBoard* board, const uint32_t& max_depth, const uint32_t playerType)
	{
		std::queue<MinimaxBoard*> q;
		int nsupcase = 0;
		uint32_t type = playerType;

		q.push(board);

		// simulate to max_depth before 1 step
		for (uint32_t i = 1; (i < max_depth) && !q.empty(); ++i)
		{
			MinimaxBoard* cur = q.front();
			q.pop();

			auto* placables = cur->getPlacables();
			for (auto stone : *placables)
			{
				MinimaxBoard* next = cur;
				next->put(type, stone.lock().get());
				
				if (cur->isover()) ++nsupcase;
				else q.push(next);
			}
			type = (i % 2) + 1;
		}

		// count superior cases
		while (!q.empty())
		{
			MinimaxBoard* cur = q.front();
			nsupcase += cur->issuperior(playerType);

			//delete cur;
			q.pop();
		}
		return nsupcase;
	}
};
