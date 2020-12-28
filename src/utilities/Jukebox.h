#pragma once
#include <array>
#include <algorithm>
#include <memory>
#include <SFML/Audio.hpp>

namespace yothello
{
	constexpr uint32_t NSOUND = 9;
	constexpr uint32_t FANFARE = 0;
	constexpr uint32_t IDX_OFFSET = 1;

	class Jukebox
	{
	public:
		static const std::string MUSIC_PREFIX;
		static const std::string MUSIC_SUFFIX;
		static const std::string SOUND_BLACK;
		static const std::string SOUND_WHITE;
		static const std::string SOUND_BACKGROUND;

	private:
		std::array<std::shared_ptr<sf::Music>, NSOUND> jukebox;
		std::weak_ptr<sf::Music> playingNow;

	public:
		Jukebox(const std::string& player);
		~Jukebox();

		bool done() const { return (playingNow.lock()->getStatus() == sf::Music::Status::Stopped); }
		int onplaying() const
		{
			const int index = (std::find_if(jukebox.begin() + IDX_OFFSET, jukebox.end(),
				[&](std::shared_ptr<sf::Music> music) { return (music == playingNow.lock()); }) - jukebox.begin());
			return (index - IDX_OFFSET);
		}

		void update() { if (done()) randomPlay(); }
		void tune(const int& volume);

		void play(const uint32_t number);
		void randomPlay();
		void fanfare() const;
		void stop() const;
	};
}