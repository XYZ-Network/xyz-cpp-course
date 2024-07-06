#pragma once
#include "SFML/Graphics.hpp"


namespace ArkanoidGame
{
	class GameObject
	{
	public:
		GameObject(const std::string& textureId, const sf::Vector2f& position, float width, float height);
		virtual ~GameObject() = default;
		
		virtual void Update(float timeDelta) = 0;
		virtual void Draw(sf::RenderWindow& window);

		const sf::Vector2f& GetPosition() const { return sprite.getPosition(); }
		sf::FloatRect GetRect() const { return sprite.getGlobalBounds(); }
		virtual void restart();
	protected:
		sf::Sprite sprite;
		sf::Texture texture;
		const sf::Vector2f startPosition;
	};
}


