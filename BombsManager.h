#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <string.h>

#include "DrawManager.h"
#include "World.h"
#include "MatPos.h"
#include "Bomb.h"

using namespace std;

class BombsManager
{
public:
	BombsManager(World* world, const char* bombFireTexture, const char* bombExplosionTexture, const char* explosionBodyTexture);
	~BombsManager();

	bool CanPutBomb(string playerName, int maxBombs);
	void PutBomb(MatPos bombPos, int lenght, string playerName);
	void Update(float dt);
	void Draw(DrawManager& drawManager);

private:
	void RemoveBombFromMap(Bomb* bomb);

	World* world;
	const char* bombFireTexture;
	const char* bombExposionTexture;
	const char* explosionBodyTexture;

	list<Bomb*> bombs;

	map<string, list<Bomb*> > mapPlayerBombs;
};

