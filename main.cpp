#include <stdlib.h>
#include <vector>

#include "Constants\Constants.h"
#include "World.h"
#include "Player.h"
#include "DeadWalker.h"
#include "PlayerAI.h"
#include "Bomb.h"
#include "BombsManager.h"
#include "SurprisesManager.h"

using namespace std;
using namespace WorldConst;

int main()
{
	srand(time(NULL));
	
	sf::RenderWindow window(sf::VideoMode(NC * CELL_WIDTH, NL * CELL_HEIGHT), "BOOMER");

	vector<MatPos> playerPositions{ MatPos(1, 1), MatPos(NL - 2, NC - 2),  MatPos(1, NC - 2) };
	vector<MatPos> deadWalkerPositions{ MatPos(3, 3) };
	vector<MatPos> surprisesPositions{ MatPos(1, 2), MatPos(2, 1) };

	World world("Assets\\Files\\map.in", "Assets\\Tiles\\tiles.png", playerPositions);

	BombsManager bombsManager(&world, "Assets\\Bomb\\bombFireShort.png", "Assets\\Bomb\\bombExplosion.png", "Assets\\Bomb\\explosionBody.png");

	SurprisesManager surprisesManager(&world, "Assets\\Surprise\\surpriseSpriteSheet.png");

	Player gigi(&world, &bombsManager, &surprisesManager, "Assets\\Player\\player1.png", "Assets\\Bomb\\bomb.png", playerPositions[0], "gigi");
	Player gogu(&world, &bombsManager, &surprisesManager, "Assets\\Player\\gogu.png", "Assets\\Bomb\\bomb.png", playerPositions[1], "gogu");

	PlayerAI AI(&world, &bombsManager, &surprisesManager, "Assets\\Player\\AI2.png", "Assets\\Bomb\\bomb.png", playerPositions[2], "Professor");

	DeadWalker skeleton(&world, &surprisesManager, "Assets\\Player\\skeleton.png", deadWalkerPositions[0], "Glenn");

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			gigi.SetInvincible();
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			gogu.SetInvincible();
		}

		dt = elapsedTime.asSeconds();

		world.Update(dt);
		gigi.Update(dt);
		gogu.Update(dt);
		skeleton.Update(dt);

		AI.Update(dt);

		bombsManager.Update(dt);

		window.clear(BG_COLOR);
		//system("cls");

		world.Draw(window);

		surprisesManager.Draw(window);

		gigi.Draw(window);
		gogu.Draw(window);
		bombsManager.Draw(window);
		skeleton.Draw(window);

		AI.Draw(window);

		bombsManager.Draw(window);

		window.display();
	}

	return 0;
}