#include "MouseInput.h"
using namespace yothello;

namespace MouseEventPosition
{
	inline Position clickToPos(const sf::Event& event) { return { event.mouseButton.x, event.mouseButton.y }; }
	inline Position cursorToPos(const sf::Event& event) { return { event.mouseMove.x, event.mouseMove.y }; }
}

namespace InputEventDiscrim
{
	inline bool isMouseClicked(const sf::Event& event) { return (event.type == sf::Event::MouseButtonPressed); }
	inline bool isMouseMoved(const sf::Event& event) { return (event.type == sf::Event::MouseMoved); }
	inline bool isKeyPressed(const sf::Event& event) { return (event.type == sf::Event::KeyPressed); }
	inline bool isAnyButtonPressed(const sf::Event& event) { return isMouseClicked(event) || isKeyPressed(event); }
}


void MouseInput::notifyDrag(const float infimum, const float supremum)
{
	if (!listener) return;

	Position v = position - prev;
	v.col = 0;

	const sf::Vector2f preview = listener->getPosition() + v.toVector2D();
	if (preview.x < infimum || preview.x > supremum)
		return;
	listener->move(v.toVector2D());
	prev = position;
}

void MouseInput::captureEvent(const sf::Event& event)
{
	using namespace MouseEventPosition;
	
	if (InputEventDiscrim::isMouseClicked(event))
		position = clickToPos(event);
	else if (InputEventDiscrim::isMouseMoved(event))
		position = cursorToPos(event);

	state->handleInput(event.type);
}
