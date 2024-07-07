#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

namespace ArkanoidGame
{
	class IColladiable {
	protected:
		virtual void OnHit() = 0;
	public:
		virtual bool CheckCollision(std::shared_ptr<IColladiable> collidable) {
			if (GetCollision(collidable)) {
				OnHit();
				collidable->OnHit();
				return true;
			}
			return false;
		}

		virtual bool GetCollision(std::shared_ptr<IColladiable> collidable) const = 0;
	};
}