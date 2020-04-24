#include "Player.h"

using namespace PlayerConst;

Player::Player(World* world, BombsManager* bombsManager, const char* texture, MatPos pos, string name) :
	BombPlayer(world, bombsManager, texture, pos, name)
{
}

Player::~Player()
{
}

