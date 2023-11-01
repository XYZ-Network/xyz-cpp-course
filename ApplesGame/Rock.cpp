#include "Rock.h"
#include "Game.h"

namespace ApplesGame
{
	void InitRock(Rock& rock, const Game& game)
	{
		rock.sprite.setTexture(game.rockTexture);
		SetSpriteSize(rock.sprite, ROCK_SIZE, ROCK_SIZE);
		SetSpriteRelativeOrigin(rock.sprite, 0.5f, 0.5f);
	}

	void SetRockPosition(Rock& rock, const Position2D& position)
	{
		rock.position = position;
	}

	Rectangle GetRockCollider(const Rock& rock)
	{
		return { { rock.position.x - ROCK_SIZE / 2.f, rock.position.y - ROCK_SIZE / 2.f },
					{ ROCK_SIZE, ROCK_SIZE } };
	}

	void DrawRock(Rock& rock, sf::RenderWindow& window)
	{
		rock.sprite.setPosition(rock.position.x, rock.position.y);
		window.draw(rock.sprite);
	}

}

