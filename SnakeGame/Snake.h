#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include <list>
#include <array>

namespace SnakeGame
{
	enum class SnakeDirection
	{
		Up = 0,
		Right,
		Down,
		Left
	};

	enum class SnakePart : uint8_t
	{
		Head = 0,
		Body,
		BodyBend,
		Tail,
		Count
	};

	struct Snake
	{
		std::list<sf::Sprite> body;
		std::list<sf::Sprite>::iterator head;
		std::list<sf::Sprite>::iterator tail;
		float speed = 0.f; // Pixels per second
		SnakeDirection direction = SnakeDirection::Up;
		SnakeDirection prevDirection = SnakeDirection::Up;
		std::array<sf::Texture, (size_t)SnakePart::Count> textures;
	};

	void LoadSnakeTextures(Snake& snake);
	void InitSnake(Snake& snake);
	void MoveSnake(Snake& snake, float timeDelta);
	void GrowSnake(Snake& snake);
	void DrawSnake(Snake& snake, sf::RenderWindow& window);

	bool HasSnakeCollisionWithRect(const Snake& snake, const sf::FloatRect& rect);
	bool CheckSnakeCollisionWithHimself(Snake& snake);
	bool CheckSnakeCollisionWithSprite(Snake& snake, const sf::Sprite& sprite);
	
	sf::Vector2f GetDirectionVector(SnakeDirection direction);	
}
