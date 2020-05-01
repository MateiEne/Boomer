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
	BombPlayer(World* world, BombsManager* bombsManager, const char* texture, const char* bombTexture, MatPos pos, string name);
	
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	void PutBomb();

protected:
	bool CanMove();

private:
	void UpdatePutBomb(float dt);
	bool CanPutBomb();
	void FireBomb();

	void InitBombSprite();
	void InitBombAnimations();
	void InitAnimation(Animation<sf::IntRect>& animation, const int count, const int l, const int frames[]);
	void InitBombCreationAnimation();

	sf::Texture bombTexture;
	sf::Sprite bombSprite;
	sf::Vector2f bombScale;

	BombsManager* bombsManager;

	bool putBomb;

	//Animation<sf::IntRect> putBombRightAnimation;
	//Animation<sf::IntRect> putBombLeftAnimation;
	//Animation<sf::IntRect> putBombUpAnimation;
	Animation<sf::IntRect> putBombDownAnimation;
	Animation<float> bombCreationAnimation;
};

