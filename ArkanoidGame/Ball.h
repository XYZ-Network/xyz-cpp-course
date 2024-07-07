#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "ICollidable.h"

namespace ArkanoidGame
{
	class Ball final : public GameObject, public IColladiable
	{
	public:
		Ball(const sf::Vector2f& position);
		~Ball() = default;
		void Update(float timeDelta) override;

		void InvertDirectionX();
		void InvertDirectionY();

		bool GetCollision(std::shared_ptr<IColladiable> collidable) const  override;
		void ChangeAngle(float x);
	private:
		void OnHit();
		sf::Vector2f direction;
		float lastAngle = 90;
	};
}


