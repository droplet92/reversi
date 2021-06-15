#pragma once
#include <SFML/Graphics.hpp>

using etype = sf::Event::EventType;

namespace reversi
{
	class MouseInput;

	enum class EMouseState { NONE, CLICK, MOVE, RELEASE, DRAG, DROP };

	/* State Pattern */
	class MouseState
	{
	protected:
		MouseInput* owner;

	public:
		MouseState(MouseInput* owner) :owner(owner) {}

		virtual void handleInput(const etype& e) = 0;
		virtual void enter() = 0;
		virtual void wait() = 0;
		virtual EMouseState getState() const = 0;
	};

	/* Single States */
	class MouseNone : public MouseState
	{
	public:
		MouseNone(MouseInput* owner) :MouseState(owner) {}

		void handleInput(const etype& e) final;
		void enter() final;
		void wait() final {}
		EMouseState getState() const { return EMouseState::NONE; }
	};

	class MouseOnClick : public MouseState
	{
	public:
		MouseOnClick(MouseInput* owner) :MouseState(owner) {}

		void handleInput(const etype& e) final;
		void enter() final;
		void wait() final {}
		EMouseState getState() const { return EMouseState::CLICK; }
	};

	class MouseOnMove : public MouseState
	{
	public:
		MouseOnMove(MouseInput* owner) :MouseState(owner) {}

		void handleInput(const etype& e) final;
		void enter() final;
		void wait() final {}
		EMouseState getState() const { return EMouseState::MOVE; }
	};

	class MouseOnRelease : public MouseState
	{
	public:
		MouseOnRelease(MouseInput* owner) :MouseState(owner) {}

		void handleInput(const etype& e) final;
		void enter() final;
		void wait() final;
		EMouseState getState() const { return EMouseState::RELEASE; }
	};

	/* Multiple States */
	class MouseOnDrag : public MouseState
	{
	public:
		MouseOnDrag(MouseInput* owner) :MouseState(owner) {}

		void handleInput(const etype& e) final;
		void enter() final;
		void wait() final {}
		EMouseState getState() const { return EMouseState::DRAG; }
	};

	class MouseOnDrop : public MouseState
	{
	public:
		MouseOnDrop(MouseInput* owner) :MouseState(owner) {}

		void handleInput(const etype& e) final;
		void enter() final;
		void wait() final;
		EMouseState getState() const { return EMouseState::DROP; }
	};
}