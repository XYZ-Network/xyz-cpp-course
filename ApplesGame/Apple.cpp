#include "Apple.h"

void InitApple(Apple& apple)
{
	apple.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

	apple.shape.setRadius(APPLE_SIZE / 2.f);
	apple.shape.setFillColor(sf::Color::Green);
	apple.shape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
	apple.shape.setPosition(apple.position.x, apple.position.y);
}
