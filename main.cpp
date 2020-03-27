#include "World.h"
#include "Player.h"
#include "Constants.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(NC * CELL_WIDTH, NL * CELL_HEIGHT), "BOOMER");

	World world("Assets\\Files\\map.in", "Assets\\Tiles\\tiles.png");
	Player player("Assets\\Player\\player1.png", MatPos(1, 1));

	sf::Clock frameClock;
	sf::Time elapsedTime;
	float dt;
	
	while (window.isOpen())
	{
		elapsedTime = frameClock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || 
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		dt = elapsedTime.asSeconds();

		player.Update(dt);



		window.clear(BG_COLOR);

		world.Draw(window);
		player.Draw(window);

		window.display();
	}

	return 0;
}