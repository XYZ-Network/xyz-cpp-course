#pragma once
#include "Ball.h"
#include "GameObject.h"
#include "ICollidable.h"

namespace ArkanoidGame
{
	class Block : public GameObject, public IColladiable
	{
	protected:
		void OnHit();
		int hitCount = 1;
	public:
		Block(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green);
		virtual ~Block();
		bool GetCollision(std::shared_ptr<IColladiable> collidableObject) const override;
		void Update(float timeDelta) override;
		bool IsBroken();
	};
}

