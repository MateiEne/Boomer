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
#include "BasePlayer.h"
#include "SurprisesManager.h"

using namespace std;

class BombPlayer : public BasePlayer
{
public:
	BombPlayer(World* world, BombsManager* bombsManager, SurprisesManager* surpriseManger, const char* texture, const char* bombTexture, MatPos pos, string name);
	
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	void PutBomb();

protected:
	bool CanMove();
	void ResetSurpriseTime(SurpriseType surprise);
	void ResetSurprise(SurpriseType surprise);
	void BoostAbilities(SurpriseType surprise);

	void IncreaseBombsCount();
	void IncreaseBlastRadius();

private:
	void UpdatePutBomb(float dt);
	bool CanPutBomb();
	void FireBomb();

	void InitBombSprite();
	void InitBombAnimations();
	void InitBombCreationScaleAnimation();
	void InitBombCreationPositionAnimation(sf::Vector2f initialPosition);
	void ResetBombCreationAnimations(sf::Vector2f initialPosition);

	sf::Texture bombTexture;
	sf::Sprite bombSprite;

	BombsManager* bombsManager;


	bool putBomb;
	int bombsCount;
	int blastLength;
	//Animation<sf::IntRect> putBombRightAnimation;
	//Animation<sf::IntRect> putBombLeftAnimation;
	//Animation<sf::IntRect> putBombUpAnimation;
	Animation<sf::IntRect> putBombDownAnimation;
	Animation<sf::Vector2f> bombCreationScaleAnimation;
	Animation<sf::Vector2f> bombCreationPositionAnimation;
};

