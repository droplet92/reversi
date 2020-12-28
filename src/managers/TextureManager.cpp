#include "TextureManager.h"
#include <cassert>
using namespace sfManager;


std::weak_ptr<sf::Texture> TextureManager::loadTexture(const std::string path)
{
	const auto& value = cache.find(path);

	if (value != cache.end())
		return value->second;
	else
	{
		std::shared_ptr<sf::Texture> texture(new sf::Texture);

		if (!texture->loadFromFile(path))
			assert(!"Unloadable texture image path");
		texture->setSmooth(true);
		texture->setRepeated(true);
		return (cache[path] = texture);
	}
}

std::weak_ptr<sf::Texture> TextureManager::loadTexture(const std::string path, const sf::IntRect size)
{
	const auto& value = cache.find(path);

	if (value != cache.end())
		return value->second;
	else
	{
		std::shared_ptr<sf::Texture> texture(new sf::Texture);

		if (!texture->loadFromFile(path, size))
			assert(!"Unloadable texture image path");
		texture->setSmooth(true);
		texture->setRepeated(true);
		return (cache[path] = texture);
	}
}