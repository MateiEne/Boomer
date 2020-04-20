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

using namespace std;

class BasePlayer
{
public:
	BasePlayer(World* world, const char* texture, MatPos pos, string name);

	virtual void Update(float dt);
	void Draw(sf::RenderWindow& window);


protected:
	void InitSprite();
	virtual void InitAnimations();
	void InitAnimation(Animation<sf::IntRect>& animation, int count, int l);
	void ChangeAnimation(Animation<sf::IntRect>& animation, float changeFrameTime, bool loop = true);
	void InitTurnAnimation(
		Animation<sf::IntRect>& animation,
		int defaultFirstPosC,
		int defaultFirstPosL,
		int defaultSecondPosC,
		int defaultSecondPosL
	);

	bool WillCollide(sf::Vector2f desirePosition);
	bool ReachedDesirePostion();
	MatPos GetMatPlayerPosition();
	void UpdateMovement(float dt);

	World* world;
	string name;

	bool move;

	Direction direction;

	//Textures
	sf::Texture spriteSheetTexture;

	//Sprites
	sf::Sprite sprite;

	sf::Vector2f position;
	sf::Vector2f desirePosition;

	Animation<sf::IntRect>* animation;
	Animation<sf::IntRect>* prevAnimation;

	Animation<sf::IntRect> downAnimation;
	Animation<sf::IntRect> upAnimation;
	Animation<sf::IntRect> rightAnimation;
	Animation<sf::IntRect> leftAnimation;

	/*Animation turnLeftAnimation;
	Animation turnRightAnimation;
	Animation turnUpAnimation;
	Animation turnDownAnimation;*/
};

