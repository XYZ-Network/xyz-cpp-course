#include "Snake.h"
#include <assert.h>
#include "GameSettings.h"
#include "Sprite.h"


namespace
{
	// id textures
	const std::string HEAD_TEXTURE_ID = "Head";
	const std::string BODY_TEXTURE_ID = "Body";
	const std::string BODY_BEND_TEXTURE_ID = "BodyBend";
	const std::string TAIL_TEXTURE_ID = "Tail";

	std::list<sf::Sprite>::iterator GetNextIterator(SnakeGame::Snake& snake, std::list<sf::Sprite>::iterator it)
	{
		auto nextIt = std::next(it);
		if (nextIt == snake.body.end()) {
			nextIt = snake.body.begin();
		}
		return nextIt;
	}

	std::list<sf::Sprite>::iterator GetPrevIterator(SnakeGame::Snake& snake, std::list<sf::Sprite>::iterator it)
	{
		auto prevIt = it == snake.body.begin()
			? std::prev(snake.body.end())
			: std::prev(it);
		return prevIt;
	}

	void SetHeadSprite(SnakeGame::Snake& snake, std::list<sf::Sprite>::iterator it)
	{
		auto prevIt = GetPrevIterator(snake, it);
		float angle = -90.f; // Left
		if (prevIt->getPosition().y > it->getPosition().y) { // Up
			angle = 0.f;
		}
		else if (prevIt->getPosition().x < it->getPosition().x) { // Right
			angle = 90.f;
		}
		else if (prevIt->getPosition().y < it->getPosition().y) { // Down
			angle = 180.f;
		}

		it->setTexture(snake.textures[(size_t)SnakeGame::SnakePart::Head]);
		it->setRotation(angle);
	}

	void SetTailSprite(SnakeGame::Snake& snake, std::list<sf::Sprite>::iterator it)
	{
		auto nextIt = GetNextIterator(snake, it);
		float angle = -90.f; // Left
		if (nextIt->getPosition().y > it->getPosition().y) { // Up
			angle = 0.f;
		}
		else if (nextIt->getPosition().x < it->getPosition().x) { // Right
			angle = 90.f;
		}
		else if (nextIt->getPosition().y < it->getPosition().y) { // Down
			angle = 180.f;
		}
		
		it->setTexture(snake.textures[(size_t)SnakeGame::SnakePart::Tail]);
		it->setRotation(angle);
	}

	void SetBodySprite(SnakeGame::Snake& snake, std::list<sf::Sprite>::iterator it)
	{
		auto prevIt = GetPrevIterator(snake, it);
		auto nextIt = GetNextIterator(snake, it);
		float angle = 0.f; // Left
		sf::Texture* texturePtr = &snake.textures[(size_t)SnakeGame::SnakePart::BodyBend];;

		if (prevIt->getPosition().x == nextIt->getPosition().x || prevIt->getPosition().y == nextIt->getPosition().y) { // Hor or Ver
			texturePtr = &snake.textures[(size_t)SnakeGame::SnakePart::Body];
			angle = prevIt->getPosition().x != nextIt->getPosition().x ? 90.f : 0.f;
		}
		else {
			if (prevIt->getPosition().x < it->getPosition().x && it->getPosition().y > nextIt->getPosition().y ||
				prevIt->getPosition().y < it->getPosition().y && it->getPosition().x > nextIt->getPosition().x) {
				// dir: right -> up or down -> left
				angle = 0.f;
			}
			else if (prevIt->getPosition().y < it->getPosition().y && it->getPosition().x < nextIt->getPosition().x ||
				prevIt->getPosition().x > it->getPosition().x && it->getPosition().y > nextIt->getPosition().y) {
				// dir: down -> right or left -> up
				angle = 90.f;
			}
			else if (prevIt->getPosition().x > it->getPosition().x && it->getPosition().y < nextIt->getPosition().y ||
				prevIt->getPosition().y > it->getPosition().y && it->getPosition().x < nextIt->getPosition().x) {
				// dir: left -> down or up -> right
				angle = 180.f;
			}
			else if (prevIt->getPosition().y > it->getPosition().y && it->getPosition().x > nextIt->getPosition().x ||
				prevIt->getPosition().x < it->getPosition().x && it->getPosition().y < nextIt->getPosition().y) {
				// dir: up -> left or right -> down
				angle = -90.f;
			}
		}
		
		it->setTexture(*texturePtr);
		it->setRotation(angle);
	}
}

namespace SnakeGame
{
	void LoadSnakeTextures(Snake& snake)
	{
		assert(snake.textures[(size_t)SnakePart::Head].loadFromFile(TEXTURES_PATH + HEAD_TEXTURE_ID + ".png"));
		assert(snake.textures[(size_t)SnakePart::Body].loadFromFile(TEXTURES_PATH + BODY_TEXTURE_ID + ".png"));
		assert(snake.textures[(size_t)SnakePart::BodyBend].loadFromFile(TEXTURES_PATH + BODY_BEND_TEXTURE_ID + ".png"));
		assert(snake.textures[(size_t)SnakePart::Tail].loadFromFile(TEXTURES_PATH + TAIL_TEXTURE_ID + ".png"));
	}

	void InitSnake(Snake& snake)
	{
		// Init snake state
		for (int i = 0; i < INITIAL_SNAKE_SIZE; ++i) {
			sf::Sprite sprite;

			if (!i) {
				InitSprite(sprite, SNAKE_SIZE, SNAKE_SIZE, snake.textures[(size_t)SnakePart::Head]);
			}
			else if (i + 1 == INITIAL_SNAKE_SIZE) {
				InitSprite(sprite, SNAKE_SIZE, SNAKE_SIZE, snake.textures[(size_t)SnakePart::Tail]);
			}
			else {
				InitSprite(sprite, SNAKE_SIZE, SNAKE_SIZE, snake.textures[(size_t)SnakePart::Body]);
			}
			
			sprite.setPosition({ (float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEGHT / 2.f + SNAKE_SIZE * i });
			snake.body.push_front(sprite);
		}
		snake.head = --snake.body.end();
		snake.tail = snake.body.begin();
		
		snake.speed = INITIAL_SPEED;
		snake.direction = SnakeDirection::Up;
	}

	void MoveSnake(Snake& snake, float timeDelta)
	{
		const sf::Vector2f direction = GetDirectionVector(snake.direction);
		auto prevHead = snake.head;

		snake.tail->setPosition(snake.head->getPosition() + direction);
		snake.head = snake.tail;
		snake.tail = GetNextIterator(snake, snake.tail);
		
		// Update textures
		SetHeadSprite(snake, snake.head);
		SetTailSprite(snake, snake.tail);
		SetBodySprite(snake, prevHead);
	}

	void GrowSnake(Snake& snake)
	{
		auto prevHead = snake.head;

		sf::Sprite sprite = *snake.head;
		sprite.setPosition(snake.head->getPosition() + GetDirectionVector(snake.direction));
		snake.head = snake.body.insert(++snake.head, sprite);

		// Set correct sprite for new part of body
		SetBodySprite(snake, prevHead);
	}

	bool HasSnakeCollisionWithScreenBorder(const Snake& snake, const sf::FloatRect& rect)
	{
		bool result = rect.contains(snake.head->getPosition());
		return !result;
	}

	bool CheckSnakeCollisionWithHimself(Snake& snake)
	{
		return FullCheckCollisions(snake.body.begin(), snake.head, *snake.head) ||
			FullCheckCollisions(std::next(snake.head), snake.body.end(), *snake.head);
	}

	sf::Vector2f GetDirectionVector(SnakeDirection direction)
	{
		sf::Vector2f result;
	
		switch (direction)
		{
			case SnakeDirection::Up:
			{
				result = { 0.f, -SNAKE_SIZE };
				break;
			}
			case SnakeDirection::Right:
			{
				result = { SNAKE_SIZE, 0.f };
				break;
			}
			case SnakeDirection::Down:
			{
				result = { 0.f, SNAKE_SIZE };
				break;
			}
			case SnakeDirection::Left:
			{
				result = { -SNAKE_SIZE, 0.f };
				break;
			}
		}

		return result;
	}
}
