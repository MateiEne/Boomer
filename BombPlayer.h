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
#include "BasePlayer.h"

using namespace std;

class BombPlayer : public BasePlayer
{
public:
	BombPlayer(World* world, BombsManager* bombsManager, const char* texture, MatPos pos, string name);
	
	void Update(float dt);
	void PutBomb();

protected:
	bool CanMove();

private:
	void UpdatePutBomb();
	bool CanPutBomb();
	void FireBomb();

	void InitBombAnimations();

	BombsManager* bombsManager;

	bool putBomb;

	Animation<sf::IntRect> putBombRightAnimation;
	Animation<sf::IntRect> putBombLeftAnimation;
	Animation<sf::IntRect> putBombUpAnimation;
	Animation<sf::IntRect> putBombDownAnimation;
};

