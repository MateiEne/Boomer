#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <string.h>

#include "World.h"
#include "MatPos.h"
#include "Bomb.h"

using namespace std;

class BombsManager
{
public:
	BombsManager(World* world, const char* bombTexture, const char* explosionTexture);
	~BombsManager();

	bool CanPutBomb(string playerName, int maxBombs);
	void PutBomb(MatPos bombPos, int lenght, string playerName);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

private:
	void RemoveBombFromMap(Bomb* bomb);

	World* world;
	const char* bombTexture;
	const char* explosionTexture;

	list<Bomb*> bombs;

	map<string, list<Bomb*> > mapPlayerBombs;
};

