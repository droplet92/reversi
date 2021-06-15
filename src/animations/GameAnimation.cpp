#include "GameAnimation.h"
using namespace reversi;

const sf::Vector2f GameAnimation::ANIMATION_POS_BIG{ 100.f,100.f };
const sf::Vector2f GameAnimation::ANIMATION_POS_SMALL{ 250.f,250.f };

const bool GameAnimation::EXPIRES = true;
const bool GameAnimation::NOT_EXPIRES = false; 

const std::string GameAnimation::BLACK_NAME = "black";
const std::string GameAnimation::WHITE_NAME = "white";
const std::string GameAnimation::TITLE_NAME = "title";
const std::string GameAnimation::PASS_NAME = "pass";
const std::string GameAnimation::WAITING_NAME = "waiting";
const std::string GameAnimation::DRAW_NAME = "draw";


GameAnimation::GameAnimation(
	const std::string animationPath,
	const sf::Vector2f pos,
	const bool expires,
	const std::function<bool(sf::Sprite*, const float)> effect,
	const uint8_t alpha
) :
	GameObject(animationPath, pos),
	effect(effect),
	_done(false),
	_expires(expires),
	frame(0u),
	now(0u),
	initState{ alpha, false }
{
}

GameAnimation::GameAnimation(
	const std::string animationPath,
	const sf::Vector2f pos,
	const sf::IntRect size,
	uint32_t frame,
	const bool expires,
	const std::function<bool(sf::Sprite*, const float)> effect,
	const uint8_t alpha
) :
	GameObject(animationPath, pos),
	effect(effect),
	_done(false),
	_expires(expires),
	frame(frame),
	now(0u),
	initState{ alpha, false }
{
	setTextureRect(size);
}

void GameAnimation::init()
{
	_done = initState._done;
	now = 0u;
	toTranslucency(initState.alpha);

	auto rect = getTextureRect();
	rect.top = 0;
	setTextureRect(rect);
}

void GameAnimation::update(const float dt)
{
	if (expired()) return;

	if (!_done)
		_done = effect(this, dt);

	if (frame)
	{
		constexpr float FRAME_MS = 0.0625f;
		static float elapsed = 0.0f;
		elapsed += dt;
		
		if ((now < frame) && (now * FRAME_MS < elapsed))
		{
			sf::IntRect rect = getTextureRect();
			rect.top += rect.height;
			setTextureRect(rect);
			++now;
		}
		else if (now >= frame)
		{
			elapsed = 0.0f;
			_done = true;
			if (!_expires) init();
		}
	}
}
