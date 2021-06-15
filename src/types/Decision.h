#pragma once
#include "Position.h"

namespace reversi
{
	struct Decision
	{
		BoardPosition bposition;
		const bool ready;

		Decision(const BoardPosition pos) :
			bposition(pos), ready(true)
		{
		}
		Decision(int egg = EMPTY_EGG) :ready(false)
		{
		}
		~Decision() {}
	};
}