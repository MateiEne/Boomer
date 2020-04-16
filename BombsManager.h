#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <string>

#include "World.h"
#include "MatPos.h"
#include "Bomb.h"
using namespace std;

class BombsManager
{
public:
	BombsManager(World* world);
	~BombsManager();

	void PutBomb(MatPos bombPos, string name);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

private:
	World* world;

	list<Bomb*> bombs;
};

