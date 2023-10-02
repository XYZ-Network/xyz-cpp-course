#include "Player.h"

void InitPlayer(Player& player)
{
	// Init player state
	player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
	player.speed = INITIAL_SPEED;
	player.direction = PlayerDirection::Right;

	// Init player shape
	player.shape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
	player.shape.setFillColor(sf::Color::Red);
	player.shape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
	player.shape.setPosition(player.position.x, player.position.y);
}
