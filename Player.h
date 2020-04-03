#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "MatPos.h"
#include "Animation.h"
#include "Direction.h"
#include "World.h"

using namespace std;

class Player
{
public:
	Player(World& world, const char* texture, MatPos pos);
	~Player();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void PutBomb();

private:
	void Init();
	void InitSprite();
	void InitAnimation(Animation& animation, int count, int l);
	void InitAnimation(Animation& animation, const int count, const int l, const int frames[]);
	void ChangeAnimation(Animation& animation, bool loop = true);
	void InitTurnAnimation(
		Animation& animation,
		int defaultFirstPosC,
		int defaultFirstPosL,
		int defaultSecondPosC,
		int defaultSecondPosL
	);
	bool WillCollide(sf::Vector2f desirePosition);
	void ChangeAnimationOfPutBomb(Animation& animation, bool loop = true);
	bool IsPutBombAnimation();
	bool IsMoveAnimation();
	bool ReachedDesirePostion();

	World *world;

	bool move;
	bool putBomb;

	Direction direction;

	//Textures
	sf::Texture spriteSheetTexture;

	//Sprites
	sf::Sprite sprite;

	sf::Vector2f position;
	sf::Vector2f desirePosition;

	Animation* animation;
	
	Animation downAnimation;
	Animation upAnimation;
	Animation rightAnimation;
	Animation leftAnimation;

	Animation turnLeftAnimation;
	Animation turnRightAnimation;
	Animation turnUpAnimation;
	Animation turnDownAnimation;
	
	Animation putBombRightAnimation;
	Animation putBombLeftAnimation;
	Animation putBombUpAnimation;
	Animation putBombDownAnimation;
};

