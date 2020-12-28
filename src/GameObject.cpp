#include "GameObject.h"
#include "managers/TextureManager.h"
#include <algorithm>
using namespace yothello;

const std::string GameObject::IMAGE_PREFIX = "resources/image/";
const std::string GameObject::IMAGE_SUFFIX = ".png";

const sf::Color GameObject::GRAY{ 0x66u,0x66u,0x66u };
const sf::Color GameObject::ORANGE{ 0xF9u,0xD1u,0x82u };
const sf::Color GameObject::PURPLE{ 0xD0u,0x9Au,0xACu };

GameObject::GameObject(const std::string imagename, const sf::Vector2f pos, const sf::IntRect size)
{
	const std::string path = GameObject::IMAGE_PREFIX + imagename + GameObject::IMAGE_SUFFIX;
	auto texture = sfManager::TextureManager::instance().loadTexture(path, size);
	setTexture(*texture.lock());
	setTextureRect(size);
	setPosition(pos);
}

GameObject::GameObject(const std::string imagename, const sf::Vector2f pos)
{
	const std::string path = GameObject::IMAGE_PREFIX + imagename + GameObject::IMAGE_SUFFIX;
	auto texture = sfManager::TextureManager::instance().loadTexture(path);
	setTexture(*texture.lock());
	setPosition(pos);
}

GameObject::GameObject(const sf::Vector2f pos)
{
	setPosition(pos);
}

bool yothello::GameObject::includes(const Position p) const
{
	const sf::Vector2i v = { p.row, p.col };
	const sf::Vector2i lt = { (int)getPosition().x, (int)getPosition().y };
	const sf::IntRect& rb = getTextureRect();
	const sf::IntRect box = { lt.x, lt.y, rb.width, rb.height };
	return box.contains(v);
}

bool GameObject::includes(const sf::Vector2f p) const
{
	const sf::Vector2i v = { static_cast<int>(p.x), static_cast<int>(p.y) };
	const sf::Vector2i lt = { (int)getPosition().x, (int)getPosition().y };
	const sf::IntRect& rb = getTextureRect();
	const sf::IntRect box = { lt.x, lt.y, rb.width, rb.height };
	return box.contains(v);
}

void GameObject::changeTexture(const std::string imagename, const sf::IntRect size)
{
	const std::string path = GameObject::IMAGE_PREFIX + imagename + GameObject::IMAGE_SUFFIX;
	auto texture = sfManager::TextureManager::instance().loadTexture(path, size);
	setTexture(*texture.lock());
}

void GameObject::drawTo(sf::RenderWindow& window)
{
	if (getTexture()) window.draw(*this);

	std::for_each(children.begin(), children.end(),
		[&window](GameObject* object) { object->drawTo(window); });
}