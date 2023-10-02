#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

enum class PlayerDirection
{
	Right = 0,
	Up,
	Left,
	Down
};

struct Player
{
	Position2D position;
	float speed = INITIAL_SPEED;
	PlayerDirection direction = PlayerDirection::Right;
	sf::RectangleShape shape;
};

void InitPlayer(Player& player);
