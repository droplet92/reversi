#include "InputManager.h"
using namespace yothello;

void InputManager::waitEvent()
{
	keyboardInput.waitEvent();
	mouseInput.waitEvent();
	windowInput.waitEvent();
}

void InputManager::captureEvent(sf::Event& event)
{
	keyboardInput.captureEvent(event);
	mouseInput.captureEvent(event);
	windowInput.captureEvent(event);
}
