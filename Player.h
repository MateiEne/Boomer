#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "Constants\Constants.h"
#include "MatPos.h"
#include "Animation.h"
#include "Direction.h"
#include "World.h"
#include "BombsManager.h"
#include "BombPlayer.h"

using namespace std;

class Player : public BombPlayer
{
public:
	Player(World* world, BombsManager* bombsManager, const char* texture, const char* bombTexture, MatPos pos, string name);
	~Player();
};

