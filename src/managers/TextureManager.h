#pragma once
#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace sfManager
{
	class TextureManager
	{
	private:
		std::unordered_map<std::string, std::shared_ptr<sf::Texture>> cache;

	public:
		~TextureManager()
		{
			for (auto& iter : cache)
				iter.second.reset();
		}

		static TextureManager& instance()
		{
			static TextureManager* tm = new TextureManager();
			return *tm;
		}

		std::weak_ptr<sf::Texture> loadTexture(const std::string path);
		std::weak_ptr<sf::Texture> loadTexture(const std::string path, const sf::IntRect size);

	private:
		TextureManager()
		{
			cache.reserve(20);	// # of images
		}
	};
}