#pragma once
#include <SFML/Window/Event.hpp>

namespace reversi
{
	class GameInput
	{
	public:
		virtual void captureEvent(const sf::Event& event) = 0;
	};
}