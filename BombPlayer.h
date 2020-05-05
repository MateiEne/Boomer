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
#include "SurprisesManager.h"

using namespace std;

class BombPlayer : public BasePlayer
{
public:
	BombPlayer(World* world, BombsManager* bombsManager, SurprisesManager* surpriseManger, const char* texture, MatPos pos, string name);
	
	void Update(float dt);
	void PutBomb();

protected:
	bool CanMove();

private:
	void UpdatePutBomb();
	bool CanPutBomb();
	void FireBomb();

	void InitBombAnimations();
	void InitAnimation(Animation<sf::IntRect>& animation, const int count, const int l, const int frames[]);

	BombsManager* bombsManager;


	bool putBomb;

	Animation<sf::IntRect> putBombRightAnimation;
	Animation<sf::IntRect> putBombLeftAnimation;
	Animation<sf::IntRect> putBombUpAnimation;
	Animation<sf::IntRect> putBombDownAnimation;
};

