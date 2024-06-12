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

	class Snake
	{
	public:
		void Init();
		void LoadTextures();
		void Move(float timeDelta);
		void Grow();
		void Draw(sf::RenderWindow& window);

		bool HasCollisionWithRect(const sf::FloatRect& rect);
		bool CheckCollisionWithHimself();
		bool CheckCollisionWithSprite(const sf::Sprite& sprite);

		void SetDirection(SnakeDirection newDirection) { direction = newDirection; }
		void SetSpeed(float value) { speed = value; }

		std::list<sf::Sprite> GetBody() const { return body; }
		std::list<sf::Sprite>::iterator GetTail() { return body.begin(); }
		std::list<sf::Sprite>::iterator GetHead() { return --body.end(); }
		float GetSpeed() const { return speed; }
		SnakeDirection GetDirection() const { return direction; }

	private:
		sf::Vector2f GetDirectionVector(SnakeDirection direction);
		void UpdateHeadSprite();
		void UpdateTailSprite();
		sf::Sprite GetRotationSprite(SnakeDirection oldDirection, SnakeDirection newDirection);

	private:
		std::list<sf::Sprite> body;
		float speed = 0.f; // Pixels per second
		SnakeDirection direction = SnakeDirection::Up;
		SnakeDirection prevDirection = SnakeDirection::Up;
		std::array<sf::Texture, (size_t)SnakePart::Count> textures;
	};
}
