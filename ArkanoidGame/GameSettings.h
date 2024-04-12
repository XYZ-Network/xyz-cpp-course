#pragma once
#include <string>

namespace SnakeGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";

	// Game settings constants
	const float SNAKE_SIZE = 20.f;
	const unsigned int INITIAL_SNAKE_SIZE = 3;
	const unsigned int APPLE_SIZE = 20;
	const unsigned int ROCK_SIZE = 15;
	const float INITIAL_SPEED = 200.f;	// 
	const float ACCELERATION = 10.f;	// For each eaten apple snake speed will be increased by this value
	const int MAX_APPLES = 80;
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEGHT = 600;
	const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps
	const unsigned int ROCKS_COUNT = 20;

	const int MAX_RECORDS_TABLE_SIZE = 5;
	extern const char* PLAYER_NAME; // We need to define this constant in some CPP

	const std::string GAME_NAME = "SnakeGame";
}
