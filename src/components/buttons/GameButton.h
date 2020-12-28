#pragma once
#include "../../animations/GameAnimation.h"
#include "../../GameInterfaces.h"
#include "../../inputs/MouseInput.h"
#include <type_traits>

namespace yothello
{
	class AnimationButton : public IButton, public GameAnimation
	{
	public:
		AnimationButton(
			const std::string animationPath,
			const sf::Vector2f pos,
			const sf::IntRect size,
			uint32_t frame,
			const std::function<bool(sf::Sprite*, const float)> effect = none,
			const uint8_t alpha = 0xFFu
		) :
			GameAnimation(animationPath, pos, size, frame, GameAnimation::NOT_EXPIRES, effect, alpha)
		{
		}
		~AnimationButton() final {}

		bool onClick(const MouseInput& mouseInput) final
		{
			return (includes(mouseInput.position) && (mouseInput.onRelease() || mouseInput.onDrop()));
		}
		void update(const float dt)
		{
			if (done())
			{
				init();
				resetColor();
			}
			GameAnimation::update(dt);
		}
	};

	class PlainButton : public IButton, public GameObject
	{
	private:
		bool is_available = true;

	public:
		PlainButton(const std::string imagename, const sf::Vector2f pos, const sf::IntRect size) :
			GameObject(imagename, pos, size)
		{
		}
		PlainButton(const std::string imagename, const sf::Vector2f pos) :
			GameObject(imagename, pos)
		{
		}
		PlainButton(const sf::Vector2f pos) :
			GameObject(pos)
		{
		}
		PlainButton() {}
		~PlainButton() override {}

		bool onClick(const MouseInput& mouseInput) override
		{
			if (!is_available) return false;
			return (includes(mouseInput.position) && (mouseInput.onRelease() || mouseInput.onDrop()));
		}
		bool isAvailable() const { return is_available; }

		void setAvailable()
		{
			resetColor();	// setVisible
			is_available = true;
		}
		void setUnavailable()
		{
			setInvisible();
			is_available = false;
		}
	};

	template <typename T>	// T must be a kind of GameObject
	class PopupButton : public PlainButton
	{
	protected:
		T popup;
		bool toggle;

	public:
		PopupButton(const std::string imagename, const sf::Vector2f pos, const sf::IntRect size) :
			PlainButton(imagename, pos, size),
			popup(),
			toggle(false)
		{
			static_assert(std::is_base_of_v<GameObject, T>, "T must be a kind of GameObject");
		}
		~PopupButton() final {}

		bool onfocus() const { return toggle; }
		T& getPopup() { return popup; }

		template <typename T>
		void pop()
		{
			toggle = !toggle;
			if (toggle) popup.show();
			else popup.close();
		}
	};
}