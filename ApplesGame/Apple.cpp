#include "Apple.h"
#include "Game.h"

namespace ApplesGame
{
	void InitApple(Apple& apple, const Game& game)
	{
		apple.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		apple.sprite.setTexture(game.appleTexture);
		SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
		SetSpriteRelativeOrigin(apple.sprite, 0.5f, 0.5f);
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		apple.sprite.setPosition(apple.position.x, apple.position.y);
		window.draw(apple.sprite);
	}

}

