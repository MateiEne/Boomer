#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Constants.h"
#include "MatPos.h"
#include "Animation.h"
#include "Direction.h"
#include "World.h"

using namespace std;

class DeadWalker
{
public:
	DeadWalker(World& world, const char* texture, MatPos pos);
	~DeadWalker();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

private:
	void InitSprite();
	void ChangeAnimation(Animation& animation, float changeFrameTime, bool loop = true);
	void InitAnimation(Animation& animation, int count, int l);
	void InitAnimation(Animation& animation, const int count, const MatPos frames[]);
	void Init();

	bool IsMoveAnimation();
	bool ReachedDesirePostion();

	void MoveRigt();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void MoveRandom();
	void Stay();

	void MoveRandomOrStay();

	bool WillCollide(sf::Vector2f desirePosition);

	World* world;
	
	bool move;

	//Textures
	sf::Texture spriteSheetTexture;

	//Sprites
	sf::Sprite sprite;


	sf::Vector2f position;
	sf::Vector2f desirePosition;

	Animation* animation;
	Direction direction;

	Animation downAnimation;
	Animation upAnimation;
	Animation rightAnimation;
	Animation leftAnimation;
	Animation stayAnimation;
};

