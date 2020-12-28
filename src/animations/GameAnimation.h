#pragma once
#include "../GameObject.h"
#include <functional>

namespace yothello
{
	extern bool none(sf::Sprite* sprite, const float dt);

	class GameAnimation : public GameObject
	{
	public:
		static const sf::Vector2f ANIMATION_POS_BIG;
		static const sf::Vector2f ANIMATION_POS_SMALL;

		static const bool EXPIRES;
		static const bool NOT_EXPIRES;

		static const std::string BLACK_NAME;
		static const std::string WHITE_NAME;
		static const std::string TITLE_NAME;
		static const std::string PASS_NAME;
		static const std::string WAITING_NAME;
		static const std::string DRAW_NAME;

	protected:
		bool _done;
		bool _expires;

	private:
		std::function<bool(sf::Sprite*, const float)> effect;
		uint32_t frame, now;

		struct InitState
		{
			const uint8_t alpha;
			const bool _done;
		} initState;

	public:
		GameAnimation(
			const std::string animationPath,
			const sf::Vector2f pos,
			const bool expires,
			const std::function<bool(sf::Sprite*, const float)> effect = none,
			const uint8_t alpha = 0x00u
		);
		GameAnimation(
			const std::string animationPath,
			const sf::Vector2f pos,
			const sf::IntRect size,
			uint32_t frame,
			const bool expires,
			const std::function<bool(sf::Sprite*, const float)> effect = none,
			const uint8_t alpha = 0x00u
		);
		~GameAnimation() override {}

		void init();

		bool done() const { return _done; }
		bool expired() const { return _done && !_expires; }

		void update(const float dt);

	protected:
		GameAnimation() :
			GameObject(),
			effect(nullptr),
			_done(true),
			_expires(NOT_EXPIRES),
			frame(0u),
			now(0u),
			initState{ 0x00u, true }
		{
		}
	};

	class NullAnimation : public GameAnimation
	{
	public:
		NullAnimation() :
			GameAnimation()
		{
		}
	};
}
