#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

namespace ArkanoidGame
{
	class Ball : public GameObject
	{
	public:
		Ball(const sf::Vector2f& position);

		void Update(float timeDelta) override;

		void InvertDirectionX();
		void InvertDirectionY();

	private:
		sf::Vector2f direction;
	};
}


