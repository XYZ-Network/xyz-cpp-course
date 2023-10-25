#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
	struct Rock
	{
		Position2D position;
		sf::RectangleShape shape;
	};

	void InitRock(Rock& rock);
}

