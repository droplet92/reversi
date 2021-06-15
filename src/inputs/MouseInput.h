#pragma once
#include "../GameInput.h"
#include "../GameObject.h"
#include "../types/Position.h"
#include "../states/MouseState.h"

namespace reversi
{
	class MouseInput : public GameInput
	{
	public:
		Position position;

	private:
		MouseState* state;
		GameObject* listener;
		Position prev;

	public:
		MouseInput() :state(new MouseNone(this)), listener(nullptr) {}

		bool isNone() const { return (state->getState() == EMouseState::NONE); }
		bool onMove() const { return (state->getState() == EMouseState::MOVE); }
		bool onClick() const { return (state->getState() == EMouseState::CLICK); }
		bool onRelease() const { return (state->getState() == EMouseState::RELEASE); }
		bool onDrag() const { return (state->getState() == EMouseState::DRAG); }
		bool onDrop() const { return (state->getState() == EMouseState::DROP); }

		void registerListener(GameObject* obj) { listener = obj; prev = position; }
		void unregisterListener() { listener = nullptr; }
		void notifyDrag(const float infimum, const float supremum);

		void changeState(MouseState* _state)
		{
			delete state;
			state = _state;
			state->enter();
		}
		void release() { changeState(new MouseOnRelease(this)); }
		void waitEvent() { state->wait(); }
		void captureEvent(const sf::Event& event) final;
	};
}