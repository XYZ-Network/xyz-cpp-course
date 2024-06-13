#include "GameObject.h"
#include "Sprite.h"

namespace ArkanoidGame
{
	void GameObject::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}
}