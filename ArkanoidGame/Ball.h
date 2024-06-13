#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

namespace ArkanoidGame
{
	class Ball : public GameObject
	{
	public:
		void Init();
		void Update(float timeDelta);

		void ReboundFromPlatform();

	private:
		sf::Vector2f direction;
	};
}


