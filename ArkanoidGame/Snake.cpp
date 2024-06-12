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
}

namespace SnakeGame
{
	void Snake::LoadTextures()
	{
		assert(textures[(size_t)SnakePart::Head].loadFromFile(TEXTURES_PATH + HEAD_TEXTURE_ID + ".png"));
		assert(textures[(size_t)SnakePart::Body].loadFromFile(TEXTURES_PATH + BODY_TEXTURE_ID + ".png"));
		assert(textures[(size_t)SnakePart::BodyBend].loadFromFile(TEXTURES_PATH + BODY_BEND_TEXTURE_ID + ".png"));
		assert(textures[(size_t)SnakePart::Tail].loadFromFile(TEXTURES_PATH + TAIL_TEXTURE_ID + ".png"));
	}

	void Snake::Init()
	{
		auto addSprite = [this](const sf::Texture& texture, const sf::Vector2f& position) {
			sf::Sprite sprite;
			InitSprite(sprite, SNAKE_SIZE, SNAKE_SIZE, texture);
			sprite.setPosition(position);
			body.push_front(sprite);
		};
		addSprite(
			textures[(size_t)SnakePart::Head],
			{ (float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEGHT / 2.f }
		);
		addSprite(
			textures[(size_t)SnakePart::Tail],
			{ (float)SCREEN_WIDTH / 2.f, (float)SCREEN_HEGHT / 2.f + SNAKE_SIZE * (INITIAL_SNAKE_SIZE - 1)}
		);
		
		speed = INITIAL_SPEED;
		prevDirection = direction = SnakeDirection::Up;
	}

	void Snake::Move(float timeDelta)
	{
		float shift = speed * timeDelta;
		const sf::Vector2f vecDirection = GetDirectionVector(direction) * shift / SNAKE_SIZE;
		auto prevHead = GetHead();

		// new rotation
		if (prevDirection != direction) {
			body.insert(body.end(), *prevHead);
			UpdateHeadSprite();
			
			*prevHead = GetRotationSprite(prevDirection, direction);
			prevHead->setPosition(GetHead()->getPosition());
		}
		GetHead()->setPosition(GetHead()->getPosition() + vecDirection);
		
		auto tail = GetTail();
		auto nextTail = std::next(tail);
		auto tailDirection = GetVectorBetweenSprites(*tail, *nextTail);
		auto dist = GetManhattanDistanceBetweenSprites(*tail, *nextTail);

		if (shift > dist) {
			shift -= dist;
			tail = body.erase(tail);
			UpdateTailSprite();
		}
		else {
			tail->setPosition(tail->getPosition() + tailDirection * shift / dist);
		}

		prevDirection = direction;
	}

	void Snake::Grow()
	{
		GetHead()->setPosition(GetHead()->getPosition() + GetDirectionVector(direction));
	}

	void Snake::Draw(sf::RenderWindow& window)
	{
		// draw direct parts of body
		for (auto it = body.begin(); it != GetHead(); ++it) {
			auto nextIt = std::next(it);
			float width = SNAKE_SIZE, height = GetManhattanDistanceBetweenSprites(*it, *nextIt) - SNAKE_SIZE;
			float angle = it->getPosition().x != nextIt->getPosition().x ? 90.f : 0.f;

			if (width > 0.f && height > 0.f) {
				sf::Sprite sprite;
				InitSprite(sprite, width, height, textures[(size_t)SnakePart::Body]);
				auto position = (it->getPosition() + nextIt->getPosition()) / 2.f;
				sprite.setPosition(position);
				sprite.setRotation(angle);
				DrawSprite(sprite, window);
			}
		}

		// draw others
		DrawSprites(body.begin(), body.end(), window);
	}

	bool Snake::HasCollisionWithRect(const sf::FloatRect& rect)
	{
		sf::Vector2f forwardPoint = GetHead()->getPosition();
		if (direction == SnakeDirection::Up) {
			forwardPoint.y -= SNAKE_SIZE / 2.f;
		}
		else if (direction == SnakeDirection::Right) {
			forwardPoint.x += SNAKE_SIZE / 2.f;
		}
		else if (direction == SnakeDirection::Down) {
			forwardPoint.y += SNAKE_SIZE / 2.f;
		}
		else {
			forwardPoint.x -= SNAKE_SIZE / 2.f;
		}

		bool result = rect.contains(forwardPoint);
		return result;
	}

	bool Snake::CheckCollisionWithHimself()
	{
		auto tail = GetTail();
		auto curIt = tail;
		auto nextIt = std::next(tail);
		while (nextIt != GetHead()) {
			auto curRect = curIt->getGlobalBounds();
			auto nextRect = nextIt->getGlobalBounds();

			sf::FloatRect unionRect;
			unionRect.top = std::min(curRect.top, nextRect.top);
			unionRect.left = std::min(curRect.left, nextRect.left);
			unionRect.width = std::fabs(curRect.left - nextRect.left) + SNAKE_SIZE;
			unionRect.height = std::fabs(curRect.top - nextRect.top) + SNAKE_SIZE;

			if (HasCollisionWithRect(unionRect)) {
				return true;
			}
			curIt = nextIt;
			nextIt = std::next(nextIt);
		}
		return false;
	}

	bool Snake::CheckCollisionWithSprite(const sf::Sprite& sprite)
	{
		auto curIt = GetTail();

		while (curIt != GetHead()) {
			auto nextIt = std::next(curIt);
			auto curRect = curIt->getGlobalBounds();
			auto nextRect = nextIt->getGlobalBounds();

			sf::FloatRect unionRect;
			unionRect.top = std::min(curRect.top, nextRect.top);
			unionRect.left = std::min(curRect.left, nextRect.left);
			unionRect.width = std::fabs(curRect.left - nextRect.left) + SNAKE_SIZE;
			unionRect.height = std::fabs(curRect.top - nextRect.top) + SNAKE_SIZE;

			if (HasCollisionWithRect(unionRect)) {
				return true;
			}
			curIt = nextIt;
		}
		return false;
	}

	sf::Vector2f Snake::GetDirectionVector(SnakeDirection direction)
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

	void Snake::UpdateHeadSprite()
	{
		float angle = 0.f; // Up
		if (direction == SnakeDirection::Right) { // Right
			angle = 90.f;
		}
		else if (direction == SnakeDirection::Down) { // Down
			angle = 180.f;
		}
		else if (direction == SnakeDirection::Left) { // Left
			angle = -90.f;
		}

		GetHead()->setTexture(textures[(size_t)SnakePart::Head]);
		GetHead()->setRotation(angle);
	}

	void Snake::UpdateTailSprite()
	{
		auto tail = GetTail();
		auto nextTail = std::next(tail);
		
		GetTail()->setTexture(textures[(size_t)SnakePart::Tail]);

		if (nextTail == body.end()) {
			return;
		}

		float angle = 0.f; // Up
		if (nextTail->getPosition().x < tail->getPosition().x) { // Left
			angle = -90.f;
		}
		else if (nextTail->getPosition().x > tail->getPosition().x) { // Right
			angle = 90.f;
		}
		else if (nextTail->getPosition().y > tail->getPosition().y) { // Down
			angle = 180.f;
		}

		tail->setRotation(angle);
	}

	sf::Sprite Snake::GetRotationSprite(SnakeDirection oldDirection, SnakeDirection newDirection)
	{
		sf::Sprite sprite;
		InitSprite(
			sprite,
			SNAKE_SIZE,
			SNAKE_SIZE,
			textures[(size_t)SnakePart::BodyBend]);

		float angle = 0.f;
		if (oldDirection == SnakeDirection::Right && newDirection == SnakeDirection::Up ||
			oldDirection == SnakeDirection::Down && newDirection == SnakeDirection::Left) {
			angle = 0.f;
		}
		else if (oldDirection == SnakeDirection::Down && newDirection == SnakeDirection::Right ||
			oldDirection == SnakeDirection::Left && newDirection == SnakeDirection::Up) {
			angle = 90.f;
		}
		else if (oldDirection == SnakeDirection::Left && newDirection == SnakeDirection::Down ||
			oldDirection == SnakeDirection::Up && newDirection == SnakeDirection::Right) {
			angle = 180;
		}
		else if (oldDirection == SnakeDirection::Up && newDirection == SnakeDirection::Left ||
			oldDirection == SnakeDirection::Right && newDirection == SnakeDirection::Down) {
			angle = -90.f;
		}

		sprite.setRotation(angle);
		return sprite;
	}
}
