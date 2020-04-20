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
	BasePlayer(World* world, BombsManager* bombsManager, const char* texture, MatPos pos, string name);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void PutBomb();

protected:
	void InitSprite();
	void InitAnimations();
	void InitAnimation(Animation<sf::IntRect>& animation, int count, int l);
	void InitAnimation(Animation<sf::IntRect>& animation, const int count, const int l, const int frames[]);
	void ChangeAnimation(Animation<sf::IntRect>& animation, float changeFrameTime, bool loop = true);
	void InitTurnAnimation(
		Animation<sf::IntRect>& animation,
		int defaultFirstPosC,
		int defaultFirstPosL,
		int defaultSecondPosC,
		int defaultSecondPosL
	);

	bool WillCollide(sf::Vector2f desirePosition);
	bool CanMove();
	bool ReachedDesirePostion();
	bool CanPutBomb();
	void FireBomb();
	MatPos GetMatPlayerPosition();
	void UpdateMovement(float dt);
	void UpdatePutBomb();

	World* world;
	BombsManager* bombsManager;
	string name;

	bool move;
	bool putBomb;

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

	Animation<sf::IntRect> putBombRightAnimation;
	Animation<sf::IntRect> putBombLeftAnimation;
	Animation<sf::IntRect> putBombUpAnimation;
	Animation<sf::IntRect> putBombDownAnimation;
};

