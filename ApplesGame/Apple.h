#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
	struct Apple
	{
		Position2D position;
		sf::CircleShape shape;
	};

	void InitApple(Apple& apple);
}

