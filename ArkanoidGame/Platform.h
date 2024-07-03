#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

namespace ArkanoidGame
{
	class Ball;

	class Platform : public GameObject
	{
	public:
		Platform(const sf::Vector2f& position);

		void Update(float timeDelta) override;
		
		bool CheckCollisionWithBall(const Ball& ball) const;

	private:
		void Move(float speed);
	};
}


