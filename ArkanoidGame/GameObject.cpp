#include "GameObject.h"
#include "Sprite.h"
#include <assert.h>


namespace ArkanoidGame
{
	GameObject::GameObject(const std::string& texturePath, const sf::Vector2f& position, float width, float height):
		startPosition(position)
	{
		assert(texture.loadFromFile(texturePath));

		InitSprite(sprite, width, height, texture);
		sprite.setPosition(position);
	}

	void GameObject::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}
	void GameObject::restart()
	{
		sprite.setPosition(startPosition);
	}

}