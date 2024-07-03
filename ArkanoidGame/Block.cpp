#include "Block.h"
#include "Sprite.h"

namespace
{
	const std::string TEXTURE_ID = "platform";
}

namespace ArkanoidGame
{
	Block::Block(const sf::Vector2f& position)
		: GameObject(TEXTURES_PATH + TEXTURE_ID + ".png", position, BLOCK_WIDTH, BLOCK_HEIGHT)
	{
		sprite.setColor(sf::Color::Green);
	}

	void Block::Update(float timeDelta)
	{

	}

	bool Block::CheckCollisionWithBall(const Ball& ball) const
	{
		const auto rect = GetRect();
		const auto ballRect = ball.GetRect();
		return rect.intersects(ballRect);
	}
}