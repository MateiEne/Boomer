#pragma once
#include <iostream>
#include <list>

#include "World.h"
#include "Bomb.h"
using namespace std;

class BombsManager
{
public:
	BombsManager(World* world);
	~BombsManager();

	Bomb* PutBomb(MatPos bombPos);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

private:
	World* world;

	list<Bomb*> bombs;
};

