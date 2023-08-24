#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame
{
	struct Apple
	{
		Position position;
		sf::Sprite sprite;
	};

	void InitApple(Apple& apple, const sf::Texture& texture);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
}
