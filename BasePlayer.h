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

	virtual void MoveUp();
	virtual void MoveRight();
	virtual void MoveLeft();
	virtual void MoveDown();
	virtual void Stay();

	virtual void Update(float dt);
	void Draw(sf::RenderWindow& window);

protected:
	void ChangeAnimation(Animation<sf::IntRect>& animation, float changeFrameTime, bool loop = true);
	bool ReachedDesirePostion();
	bool WillCollide(sf::Vector2f desirePosition);
	MatPos GetMatPlayerPosition();
	bool IsSurrounded();

	virtual bool CanMove();

private:
	void InitSprite();
	void InitAnimations();
	void InitAnimation(Animation<sf::IntRect>& animation, int count, int l);
	void InitTurnAnimation(
		Animation<sf::IntRect>& animation,
		int defaultFirstPosC,
		int defaultFirstPosL,
		int defaultSecondPosC,
		int defaultSecondPosL
	);
	void InitAnimation(Animation<sf::IntRect>& animation, const int count, const MatPos frames[]);

	void UpdateMovement(float dt);


protected:
	World* world;
	string name;

	bool isMoving;
	bool isStaying;

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

	Animation<sf::IntRect> stayAnimation;

	/*Animation turnLeftAnimation;
	Animation turnRightAnimation;
	Animation turnUpAnimation;
	Animation turnDownAnimation;*/
};

