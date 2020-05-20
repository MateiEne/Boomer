#include "Player.h"

using namespace PlayerConst;

Player::Player(World* world, BombsManager* bombsManager, SurprisesManager* surpriseManger, const char* texture, const char* bombTexture, MatPos pos, string name) :
	BombPlayer(world, bombsManager, surpriseManger, texture, bombTexture, pos, name)
{
}

Player::~Player()
{
}

