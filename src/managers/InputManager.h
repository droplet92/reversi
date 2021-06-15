#pragma once
#include <SFML/Window/Event.hpp>
#include "../inputs/KeyboardInput.h"
#include "../inputs/MouseInput.h"
#include "../inputs/WindowInput.h"

namespace reversi
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