#pragma once
#include "../GameInput.h"

namespace reversi
{
	enum class KeyboardState : int { NONE, PRESSED };

	class KeyboardInput : public GameInput
	{
	public:
		KeyboardState state = KeyboardState::NONE;

	public:
		void waitEvent() { state = KeyboardState::NONE; }
		void captureEvent(const sf::Event& event) final;
	};
}