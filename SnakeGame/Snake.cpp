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

	void SetHeadSprite(SnakeGame::Snake& snake, std::list<sf::Sprite>::iterator it)
	{
		float angle = 0.f; // Up
		if (snake.direction == SnakeGame::SnakeDirection::Right) { // Right
			angle = 90.f;
		}
		else if (snake.direction == SnakeGame::SnakeDirection::Down) { // Down
			angle = 180.f;
		}
		else if (snake.direction == SnakeGame::SnakeDirection::Left) { // Left
			angle = -90.f;
		}

		it->setTexture(snake.textures[(size_t)SnakeGame::SnakePart::Head]);
		it->setRotation(angle);
	}

	void SetTailSprite(SnakeGame::Snake& snake, std::list<sf::Sprite>::iterator it)
	{
		it->setTexture(snake.textures[(size_t)SnakeGame::SnakePart::Tail]);

		auto nextIt = std::next(it);
		if (nextIt == snake.body.end()) {
			return;
		}

		float angle = 0.f; // Up
		if (nextIt->getPosition().x < it->getPosition().x) { // Left
			angle = -90.f;
		}
		else if (nextIt->getPosition().x > it->getPosition().x) { // Right
			angle = 90.f;
		}
		else if (nextIt->getPosition().y > it->getPosition().y) { // Down
			angle = 180.f;
		}
		
		it->setRotation(angle);
	}

	sf::Sprite GetRotationSprite(
		SnakeGame::Snake& snake,
		SnakeGame::SnakeDirection oldDirection, 
		SnakeGame::SnakeDirection newDirection)
	{
		sf::Sprite sprite;
		SnakeGame::InitSprite(
			sprite,
			SnakeGame::SNAKE_SIZE,
			SnakeGame::SNAKE_SIZE,
			snake.textures[(size_t)SnakeGame::SnakePart::BodyBend]);
		
		float angle = 0.f;
		if (oldDirection == SnakeGame::SnakeDirection::Right && newDirection == SnakeGame::SnakeDirection::Up ||
			oldDirection == SnakeGame::SnakeDirection::Down && newDirection == SnakeGame::SnakeDirection::Left) {
			angle = 0.f;
		} else if (oldDirection == SnakeGame::SnakeDirection::Down && newDirection == SnakeGame::SnakeDirection::Right ||
			oldDirection == SnakeGame::SnakeDirection::Left && newDirection == SnakeGame::SnakeDirection::Up) {
			angle = 90.f;
		} else if (oldDirection == SnakeGame::SnakeDirection::Left && newDirection == SnakeGame::SnakeDirection::Down ||
			oldDirection == SnakeGame::SnakeDirection::Up && newDirection == SnakeGame::SnakeDirection::Right) {
			angle = 180;
		} else if (oldDirection == SnakeGame::SnakeDirection::Up && newDirection == SnakeGame::SnakeDirection::Left ||
			oldDirection == SnakeGame::SnakeDirection::Right && newDirection == SnakeGame::SnakeDirection::Down) {
			angle = -90.f;
		}

		sprite.setRotation(angle);
		return sprite;
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
		auto addSprite = [](Snake& snake, const sf::Texture& texture, const sf::Vector2f& position) {
			sf::Sprite sprite;
			InitSprite(sprite, SNAKE_SIZE, SNAKE_SIZE, texture);
			sprite.setPosition(position);
			snake.body.push_front(sprite);
		};
		addSprite(
			snake,
			snake.textures[(size_t)SnakePart::Head],
			{ (float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEGHT / 2.f }
		);
		addSprite(
			snake,
			snake.textures[(size_t)SnakePart::Tail],
			{ (float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEGHT / 2.f + SNAKE_SIZE * (INITIAL_SNAKE_SIZE - 1)}
		);
		snake.head = --snake.body.end();
		snake.tail = snake.body.begin();
		
		snake.speed = INITIAL_SPEED;
		snake.prevDirection = snake.direction = SnakeDirection::Up;
	}

	void MoveSnake(Snake& snake, float timeDelta)
	{
		float shift = snake.speed * timeDelta;
		const sf::Vector2f direction = GetDirectionVector(snake.direction) * shift / SNAKE_SIZE;
		auto prevHead = snake.head;

		// new rotation
		if (snake.prevDirection != snake.direction) {
			snake.head = snake.body.insert(++snake.head, *prevHead);
			SetHeadSprite(snake, snake.head);
			
			*prevHead = GetRotationSprite(snake, snake.prevDirection, snake.direction);
			prevHead->setPosition(snake.head->getPosition());
		}
		snake.head->setPosition(snake.head->getPosition() + direction);
		
		auto nextTail = std::next(snake.tail);
		auto tailDirection = GetVectorBetweenSprites(*snake.tail, *nextTail);
		auto dist = GetManhattanDistanceBetweenSprites(*snake.tail, *nextTail);

		if (shift > dist) {
			shift -= dist;
			snake.tail = snake.body.erase(snake.tail);
			SetTailSprite(snake, snake.tail);
		}
		else {
			snake.tail->setPosition(snake.tail->getPosition() + tailDirection * shift / dist);
		}

		snake.prevDirection = snake.direction;
	}

	void GrowSnake(Snake& snake)
	{
		snake.head->setPosition(snake.head->getPosition() + GetDirectionVector(snake.direction));
	}

	void DrawSnake(Snake& snake, sf::RenderWindow& window)
	{
		// draw direct parts of body
		for (auto it = snake.body.begin(); it != snake.head; ++it) {
			auto nextIt = std::next(it);
			float width = SNAKE_SIZE, height = GetManhattanDistanceBetweenSprites(*it, *nextIt) - SNAKE_SIZE;
			float angle = it->getPosition().x != nextIt->getPosition().x ? 90.f : 0.f;

			if (width > 0.f && height > 0.f) {
				sf::Sprite sprite;
				InitSprite(sprite, width, height, snake.textures[(size_t)SnakeGame::SnakePart::Body]);
				auto position = (it->getPosition() + nextIt->getPosition()) / 2.f;
				sprite.setPosition(position);
				sprite.setRotation(angle);
				DrawSprite(sprite, window);
			}
		}

		// draw others
		DrawSprites(snake.body.begin(), snake.body.end(), window);
	}

	bool HasSnakeCollisionWithRect(const Snake& snake, const sf::FloatRect& rect)
	{
		sf::Vector2f forwardPoint = snake.head->getPosition();
		if (snake.direction == SnakeDirection::Up) {
			forwardPoint.y -= SNAKE_SIZE / 2.f;
		}
		else if (snake.direction == SnakeDirection::Right) {
			forwardPoint.x += SNAKE_SIZE / 2.f;
		}
		else if (snake.direction == SnakeDirection::Down) {
			forwardPoint.y += SNAKE_SIZE / 2.f;
		}
		else {
			forwardPoint.x -= SNAKE_SIZE / 2.f;
		}

		bool result = rect.contains(forwardPoint);
		return result;
	}

	bool CheckSnakeCollisionWithHimself(Snake& snake)
	{
		auto curIt = snake.tail;
		auto nextIt = std::next(snake.tail);
		while (nextIt != snake.head) {
			auto curRect = curIt->getGlobalBounds();
			auto nextRect = nextIt->getGlobalBounds();

			sf::FloatRect unionRect;
			unionRect.top = std::min(curRect.top, nextRect.top);
			unionRect.left = std::min(curRect.left, nextRect.left);
			unionRect.width = std::fabs(curRect.left - nextRect.left) + SNAKE_SIZE;
			unionRect.height = std::fabs(curRect.top - nextRect.top) + SNAKE_SIZE;

			if (HasSnakeCollisionWithRect(snake, unionRect)) {
				return true;
			}
			curIt = nextIt;
			nextIt = std::next(nextIt);
		}
		return false;
	}

	bool CheckSnakeCollisionWithSprite(Snake& snake, const sf::Sprite& sprite)
	{
		auto curIt = snake.tail;

		while (curIt != snake.head) {
			auto nextIt = std::next(curIt);
			auto curRect = curIt->getGlobalBounds();
			auto nextRect = nextIt->getGlobalBounds();

			sf::FloatRect unionRect;
			unionRect.top = std::min(curRect.top, nextRect.top);
			unionRect.left = std::min(curRect.left, nextRect.left);
			unionRect.width = std::fabs(curRect.left - nextRect.left) + SNAKE_SIZE;
			unionRect.height = std::fabs(curRect.top - nextRect.top) + SNAKE_SIZE;

			if (HasSnakeCollisionWithRect(snake, unionRect)) {
				return true;
			}
			curIt = nextIt;
		}
		return false;
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
