#include "KeyboardInput.h"
using namespace yothello;

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
