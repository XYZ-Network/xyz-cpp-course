#pragma once
#include <SFML/Graphics.hpp>

class GameStateData
{
public:
	virtual ~GameStateData() = default;

	virtual void Init() = 0;
	virtual void HandleWindowEvent(const sf::Event& event) = 0;
	virtual void Update(float timeDelta) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
};

