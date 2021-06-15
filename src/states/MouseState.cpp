#include "MouseState.h"
#include "../inputs/MouseInput.h"
#include <iostream>
using namespace reversi;

void MouseNone::handleInput(const etype& e)
{
	switch (e)
	{
	case etype::MouseButtonPressed:
		owner->changeState(new MouseOnClick(owner));
		break;
	case etype::MouseMoved:
		owner->changeState(new MouseOnMove(owner));
		break;
	default:
		break;
	}
}

void MouseNone::enter()
{
	std::cout << "none" << std::endl;
	owner->unregisterListener();
}

void MouseOnClick::handleInput(const etype& e)
{
	switch (e)
	{
	case etype::MouseButtonReleased:
		owner->changeState(new MouseOnRelease(owner));
		break;
	case etype::MouseMoved:
		owner->changeState(new MouseOnDrag(owner));
		break;
	default:
		break;
	}
}

void MouseOnClick::enter()
{
	std::cout << "onclick" << std::endl;
}

void MouseOnMove::handleInput(const etype& e)
{
	switch (e)
	{
	case etype::MouseButtonPressed:
		owner->changeState(new MouseOnClick(owner));
		break;
	default:
		break;
	}
}

void MouseOnMove::enter()
{
	std::cout << "onmove" << std::endl;
	owner->unregisterListener();
}

void MouseOnRelease::handleInput(const etype& e)
{
	switch (e)
	{
	case etype::MouseButtonPressed:
		owner->changeState(new MouseOnClick(owner));
		break;
	case etype::MouseMoved:
		owner->changeState(new MouseOnMove(owner));
		break;
	default:
		break;
	}
}

void MouseOnRelease::enter()
{
	std::cout << "onrelease" << std::endl;
	owner->unregisterListener();
}

void MouseOnRelease::wait()
{
	owner->changeState(new MouseNone(owner));
}

void MouseOnDrag::handleInput(const etype& e)
{
	switch (e)
	{
	case etype::MouseButtonReleased:
		owner->changeState(new MouseOnDrop(owner));
		break;
	default:
		break;
	}
}

void MouseOnDrag::enter()
{
	std::cout << "ondrag" << std::endl;
}

void MouseOnDrop::handleInput(const etype& e)
{
	switch (e)
	{
	case etype::MouseButtonPressed:
		owner->changeState(new MouseOnClick(owner));
		break;
	case etype::MouseMoved:
		owner->changeState(new MouseOnMove(owner));
		break;
	default:
		break;
	}
}

void MouseOnDrop::enter()
{
	std::cout << "ondrop" << std::endl;
	owner->unregisterListener();
}

void MouseOnDrop::wait()
{
	owner->changeState(new MouseNone(owner));
}
