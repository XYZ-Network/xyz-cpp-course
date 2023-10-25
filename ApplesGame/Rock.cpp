#include "Rock.h"
#include "Game.h"

namespace ApplesGame
{
	void InitRock(Rock& rock, const Game& game)
	{
		rock.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		rock.sprite.setTexture(game.rockTexture);
		SetSpriteSize(rock.sprite, ROCK_SIZE, ROCK_SIZE);
		SetSpriteRelativeOrigin(rock.sprite, 0.5f, 0.5f);
	}

	void DrawRock(Rock& rock, sf::RenderWindow& window)
	{
		rock.sprite.setPosition(rock.position.x, rock.position.y);
		window.draw(rock.sprite);
	}

}

