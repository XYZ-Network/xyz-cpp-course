#include "Rock.h"

void InitRock(Rock& rock)
{
	rock.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

	rock.shape.setSize(sf::Vector2f(ROCK_SIZE, ROCK_SIZE));
	rock.shape.setFillColor(sf::Color::White);
	rock.shape.setOrigin(ROCK_SIZE / 2.f, ROCK_SIZE / 2.f);
	rock.shape.setPosition(rock.position.x, rock.position.y);
}
