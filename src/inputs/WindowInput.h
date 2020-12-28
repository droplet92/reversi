#pragma once
#include "../GameInput.h"

namespace yothello
{
	enum class WindowState : int { NONE, CLOSE };

	class WindowInput : public GameInput
	{
	public:
		WindowState state = WindowState::NONE;

	public:
		void waitEvent() { state = WindowState::NONE; }
		void captureEvent(const sf::Event& event) final;

		bool closed() const { return (state == WindowState::CLOSE); }
	};
}