#include "Jukebox.h"
#include <cassert>
#include <random>
using namespace yothello;

const std::string Jukebox::MUSIC_PREFIX = "resources/sound/";
const std::string Jukebox::MUSIC_SUFFIX = ".ogg";
const std::string Jukebox::SOUND_BLACK = "black";
const std::string Jukebox::SOUND_WHITE = "white";
const std::string Jukebox::SOUND_BACKGROUND = "bgm";


Jukebox::Jukebox(const std::string& player) :
	playingNow(std::weak_ptr<sf::Music>())
{
	for (int i = (player == SOUND_BACKGROUND); i < NSOUND; i++)
	{
		std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
		const std::string index = "/" + std::to_string(i);

		if (!music->openFromFile(MUSIC_PREFIX + player + index + MUSIC_SUFFIX))
			assert(!"Failed to open the sound file");
		jukebox[i] = (music);
	}
}

Jukebox::~Jukebox()
{
	for (auto& music : jukebox)
		music.reset();
}

void Jukebox::tune(const int& volume)
{
	for (auto& music : jukebox)
		if (music.use_count())
			music->setVolume(static_cast<float>(volume));
}

void Jukebox::play(const uint32_t number)
{
	stop();
	playingNow = jukebox[number];
	playingNow.lock()->play();
}

void Jukebox::randomPlay()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(IDX_OFFSET, NSOUND - IDX_OFFSET);
	play(dis(gen));
}

void Jukebox::fanfare() const
{
	stop();
	jukebox[FANFARE]->stop();
	jukebox[FANFARE]->play();
}

void Jukebox::stop() const
{
	if (!playingNow.expired())
		playingNow.lock()->stop();
}
