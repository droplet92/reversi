#pragma once
#include <SFML/Window/Event.hpp>
#include "../inputs/KeyboardInput.h"
#include "../inputs/MouseInput.h"
#include "../inputs/WindowInput.h"

namespace yothello
{
	class InputManager
	{
	// private:
	public:
		KeyboardInput keyboardInput;
		MouseInput mouseInput;
		WindowInput windowInput;

	public:
		InputManager() = default;
		~InputManager() = default;

		void waitEvent();
		void captureEvent(sf::Event& event);
	};
}