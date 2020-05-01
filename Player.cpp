#include "Player.h"

using namespace PlayerConst;

Player::Player(World* world, BombsManager* bombsManager, const char* texture, const char* bombTexture, MatPos pos, string name) :
	BombPlayer(world, bombsManager, texture, bombTexture, pos, name)
{
}

Player::~Player()
{
}

