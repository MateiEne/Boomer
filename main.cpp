#include <stdlib.h>
#include <vector>

#include "Constants.h"
#include "World.h"
#include "Player.h"
#include "DeadWalker.h"
#include "Bomb.h"

using namespace std;
using namespace WorldConst;

int main()
{
	srand(time(NULL));
	
	sf::RenderWindow window(sf::VideoMode(NC * CELL_WIDTH, NL * CELL_HEIGHT), "BOOMER");

	vector<MatPos> playerPositions{ MatPos(1, 1), MatPos(NL - 2, NC - 2) };
	vector<MatPos> deadWalkerPositions{ MatPos(3, 3) };

	World world("Assets\\Files\\map.in", "Assets\\Tiles\\tiles.png", playerPositions);

	Player gigi(world, "Assets\\Player\\player1.png", playerPositions[0]);
	Player gogu(world, "Assets\\Player\\gogu.png", playerPositions[1]);

	DeadWalker skeleton(world, "Assets\\Player\\skeleton.png", deadWalkerPositions[0]);

	Bomb bomb("Assets\\Bomb\\bomb.png", "Assets\\Bomb\\explosion.png", MatPos(3, 3), 5);
	Bomb bomb2("Assets\\Bomb\\bomb.png", "Assets\\Bomb\\explosion.png", MatPos(2, 2), 1);

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			world.Restart(playerPositions);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			gigi.MoveUp();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			gigi.MoveLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			gigi.MoveDown();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			gigi.MoveRight();
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			gigi.PutBomb();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			gogu.MoveUp();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			gogu.MoveLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			gogu.MoveDown();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			gogu.MoveRight();
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			gogu.PutBomb();
		}

		dt = elapsedTime.asSeconds();

		gigi.Update(dt);
		gogu.Update(dt);

		skeleton.Update(dt);

		bomb.Update(dt);
		bomb2.Update(dt);

		window.clear(BG_COLOR);

		world.Draw(window);
		gigi.Draw(window);
		gogu.Draw(window);
		skeleton.Draw(window);

		bomb.Draw(window);
		bomb2.Draw(window);

		window.display();
	}

	return 0;
}