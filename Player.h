#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "Constants.h"
#include "MatPos.h"
#include "Animation.h"
#include "Direction.h"
#include "Bomb.h"
#include "World.h"
#include "BombsManager.h"

using namespace std;

class Player
{
public:
	Player(World* world, BombsManager* bombManager, const char* texture, MatPos pos);
	~Player();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void PutBomb();

private:
	void InitAnimations();
	void InitSprite();
	void InitAnimation(Animation<sf::IntRect>& animation, int count, int l);
	void InitAnimation(Animation<sf::IntRect>& animation, const int count, const int l, const int frames[]);
	void InitBombs();
	void ChangeAnimation(Animation<sf::IntRect>& animation, float changeFrameTime, bool loop = true);
	void InitTurnAnimation(
		Animation<sf::IntRect>& animation,
		int defaultFirstPosC,
		int defaultFirstPosL,
		int defaultSecondPosC,
		int defaultSecondPosL
	);
	void FireBomb();

	bool WillCollide(sf::Vector2f desirePosition);
	bool CanMove();
	bool ReachedDesirePostion();
	bool CanPutBomb();
	int GetNewBombIndex();

	MatPos GetMatPlayerPosition();

	World *world;

	BombsManager* bombsManager;
	vector<Bomb*> bombs;

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

