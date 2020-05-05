#include "Player.h"

using namespace PlayerConst;

Player::Player(World* world, BombsManager* bombsManager, SurprisesManager* surpriseManger, const char* texture, MatPos pos, string name) :
	BombPlayer(world, bombsManager, surpriseManger, texture, pos, name)
{
}

Player::~Player()
{
}

