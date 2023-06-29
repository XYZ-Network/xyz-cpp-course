// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURCES_PATH = "Resources/";

int main()
{
	sf::RenderWindow window(sf::VideoMode(330, 400), "SFML works!");

	sf::Texture logo;
	if (!logo.loadFromFile(RESOURCES_PATH + "xyz-logo.png"))
	{
		return EXIT_FAILURE;
	}
	sf::Sprite logo_sprite(logo);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(logo_sprite);
		window.display();
	}

	return 0;
}
