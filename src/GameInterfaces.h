#pragma once
#include <algorithm>
#include <functional>
#include <list>

namespace yothello
{
	class MouseInput;

	class IButton
	{
	public:
		virtual bool onClick(const MouseInput& mouse) = 0;
	};

	template<typename T>
	class IComposite
	{
	protected:
		std::list<T*> children;	// [point_static]

	public:
		virtual ~IComposite() {}
		void addChild(T* child) { children.push_back(child); }
		void clear() { children.clear(); }
		void each(std::function<void(T*)> fn) { std::for_each(children.begin(), children.end(), [&](T* t) { fn(t); }); }
	};
}