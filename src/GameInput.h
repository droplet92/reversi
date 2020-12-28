#pragma once
#include <SFML/Window/Event.hpp>

namespace yothello
{
	class GameInput
	{
	public:
		virtual void captureEvent(const sf::Event& event) = 0;
	};
}