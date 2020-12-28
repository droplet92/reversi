#pragma once
#include "GameInterfaces.h"
#include "types/Position.h"
#include <list>
#include <SFML/Graphics.hpp>

namespace yothello
{
	class GameObject : public IComposite<GameObject>, public sf::Sprite
	{
	public:
		static const std::string IMAGE_PREFIX;
		static const std::string IMAGE_SUFFIX;

	private:
		static const sf::Color GRAY;
		static const sf::Color ORANGE;
		static const sf::Color PURPLE;

	public:
		GameObject(const std::string imagename, const sf::Vector2f pos, const sf::IntRect size);
		GameObject(const std::string imagename, const sf::Vector2f pos);
		GameObject(const sf::Vector2f pos);
		GameObject() {}
		virtual ~GameObject() override {};

		bool includes(const Position p) const;
		bool includes(const sf::Vector2f p) const;
		bool visible() const { return (getAlpha() != 0x00u); }

		virtual void toTranslucency(const uint8_t alpha = 0x80u)
		{
			setAlpha(alpha); each([&alpha](GameObject* obj) { obj->toTranslucency(alpha); });
		}
		virtual void resetColor() { setAlpha(0xFFu); each([](GameObject* obj) { obj->resetColor(); }); }
		virtual void setInvisible() { setAlpha(0x00u); each([](GameObject* obj) { obj->setInvisible(); }); }
		void setBright() { setAlpha(0x40u); }
		void setDark() { setColor(GRAY); }
		void highlight() { setColor(ORANGE); }
		void highlightPrevious() { setColor(PURPLE); }

		void changeTexture(const std::string imagename, const sf::IntRect size);
		void moveTo(const sf::Vector2f pos) { move(pos - getPosition()); }
		void update()
		{
			update();
			each([](GameObject* obj) { obj->update(); });
		}

		virtual void drawTo(sf::RenderWindow& window);
		virtual void show()
		{
			toTranslucency(0xD8u);
			each([](GameObject* obj) { obj->show(); });
		}
		virtual void close()
		{
			setInvisible();
			each([](GameObject* obj) { obj->close(); });
		}

	private:
		uint8_t getAlpha() const { return getColor().a; }
		void setAlpha(const uint8_t alpha) { setColor({ 0xFFu,0xFFu,0xFFu,alpha }); }

		virtual void nupdate() {}
	};
}