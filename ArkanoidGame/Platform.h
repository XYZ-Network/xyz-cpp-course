#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "ICollidable.h"

namespace ArkanoidGame
{
	class Platform : public GameObject, public IColladiable
	{
	public:
		Platform(const sf::Vector2f& position);
		void Update(float timeDelta) override;
		
		bool GetCollision(std::shared_ptr<IColladiable> collidable) const override;
		void OnHit() override {}
		bool CheckCollision(std::shared_ptr<IColladiable> collidable) override;
	private:
		void Move(float speed);
	};
}