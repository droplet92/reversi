#include "KeyboardInput.h"
using namespace reversi;

void KeyboardInput::captureEvent(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		break;
	case sf::Event::KeyReleased:
		break;
	default:
		break;
	}
}
