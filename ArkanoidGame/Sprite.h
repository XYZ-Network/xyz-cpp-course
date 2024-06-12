#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include <list>

namespace ArkanoidGame
{
	void InitSprite(sf::Sprite& sprite, float desiredWidth, float desiredHeight, const sf::Texture& texture);
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);

	/*
	* The sprite is set a random position inside the rect
	* It should not intersect with the collection of sprites
	*/
	void SetSpriteRandomPosition(sf::Sprite& sprite, const sf::FloatRect& rect, const std::list<sf::Sprite>& collection);

	sf::Vector2f GetRandomSpritePositionInRectangle(const sf::Sprite& sprite, const sf::FloatRect& rect);

	void DrawSprite(const sf::Sprite& sprite, sf::RenderWindow& window);
	template<class InputIt>
	void DrawSprites(InputIt first, const InputIt last, sf::RenderWindow& window) {
		for (; first != last; ++first) {
			DrawSprite(*first, window);
		}
	}
	
	sf::Vector2f GetVectorBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo);
	float GetManhattanDistanceBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo);

	bool CheckSpriteIntersection(const sf::Sprite& sprite1, const sf::Sprite& sprite2);	
	
	template<class InputIt>
	bool FullCheckCollisions(InputIt first, const InputIt last, const sf::Sprite& sprite) {
		for (; first != last; ++first) {
			if (CheckSpriteIntersection(*first, sprite)) {
				return true;
			}
		}
		return false;
	}
}
