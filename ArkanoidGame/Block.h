#pragma once
#include "Ball.h"
#include "GameObject.h"


namespace ArkanoidGame
{
	class Block : public GameObject
	{
	public:
		Block(const sf::Vector2f& position);
		
		void Update(float timeDelta) override;

		bool CheckCollisionWithBall(const Ball& ball) const;
	};
}

