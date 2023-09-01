#pragma once
#include "SFML/Graphics.hpp"

namespace ApplesGame
{
	struct UIState
	{
		bool isGameOverTextVisible = false;

		sf::Text scoreText;
		sf::Text inputHintText;
		sf::Text gameOverText;
	};

	void InitUI(UIState& uiState, const sf::Font& font);
	void UpdateUI(UIState& uiState, const struct GameState& gameState, float timeDelta);
	void DrawUI(UIState& uiState, sf::RenderWindow& window);
}
