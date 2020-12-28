#include "WindowInput.h"
using namespace yothello;

void WindowInput::captureEvent(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		state = WindowState::CLOSE;
		break;
	default:
		break;
	}
}
