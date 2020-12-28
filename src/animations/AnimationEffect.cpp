#include "AnimationEffect.h"
#include <algorithm>

constexpr float SEC_TO_FADE_IN = 1.0f;
constexpr float SEC_TO_FADE_OUT = 0.5f;

namespace yothello
{
	/* 1.5 seconds */
	bool popup(sf::Sprite* sprite, const float dt)
	{
		static bool fade_in_done = false;

		if (!fade_in_done)
		{
			fade_in_done = fade_in(sprite, dt);
			return false;
		}

		if (fade_out(sprite, dt))
		{
			fade_in_done = false;
			return true;
		}
		return false;
	}

	/* 1 seconds */
	bool fade_in(sf::Sprite* sprite, const float dt)
	{
		uint8_t alpha = sprite->getColor().a;
		const uint8_t delta = static_cast<uint8_t>((dt * 0xFF) / SEC_TO_FADE_IN);

		alpha = static_cast<uint8_t>(std::min(alpha + delta, 0xFF));
		sprite->setColor({ 0xFF,0xFF,0xFF,alpha });
		return (alpha == 0xFF);
	}

	/* 0.5 seconds */
	bool fade_out(sf::Sprite* sprite, const float dt)
	{
		uint8_t alpha = sprite->getColor().a;
		const uint8_t delta = static_cast<uint8_t>((dt * 0xFF) / SEC_TO_FADE_OUT);

		alpha = static_cast<uint8_t>(std::max(alpha - delta, 0x00));
		sprite->setColor({ 0xFF,0xFF,0xFF,alpha });
		return (alpha == 0x00);
	}

	bool none(sf::Sprite*, const float)
	{
		return false;
	}
}