#include "World.h"
#include "Constants.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "BOOMER");

	World world("Assets\\Files\\map.in", "Assets\\Tiles\\tiles.png");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(BG_COLOR);
		world.Draw(window);
		window.display();
	}

	return 0;
}