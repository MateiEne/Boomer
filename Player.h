#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "Constants.h"
#include "MatPos.h"
#include "Animation.h"
#include "Direction.h"
#include "World.h"
#include "BombsManager.h"
#include "BombPlayer.h"
#include "SurprisesManager.h"

using namespace std;

class Player : public BombPlayer
{
public:
	Player(World* world, BombsManager* bombsManager, SurprisesManager* surpriseManger, const char* texture, MatPos pos, string name);
	~Player();
};

