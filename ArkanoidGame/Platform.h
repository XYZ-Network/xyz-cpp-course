#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

namespace ArkanoidGame
{
	class Ball;

	class Platform : public GameObject
	{
	public:
		void Init();
		void Update(float timeDelta);
		
		bool CheckCollisionWithBall(const Ball& ball);

	private:
		void Move(float speed);
	};
}


