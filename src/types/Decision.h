#pragma once
#include "Position.h"
#define EMPTY_EGG	0

namespace reversi
{
	struct Decision
	{
		BoardPosition bposition;
		const bool ready;
		const int easter_egg;

		Decision(const BoardPosition pos) :
			bposition(pos), ready(true), easter_egg(EMPTY_EGG)
		{
		}
		Decision(int egg = EMPTY_EGG) :ready(false), easter_egg(egg)
		{
		}
		~Decision() {}
	};
}