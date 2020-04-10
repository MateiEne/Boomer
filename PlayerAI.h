#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <list>

#include "Constants.h"
#include "MatPos.h"
#include "Animation.h"
#include "Direction.h"
#include "World.h"
#include "MathUtils.h" 

class PlayerAI
{
public:
	PlayerAI(World& world, const char* texture, MatPos pos);
	~PlayerAI();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

private:
	void Init();
	void InitSprite();
	void InitAnimation(Animation& animation, int count, int l);

	void ChangeAnimation(Animation& animation, float changeFrameTime, bool loop = true);

	bool ReachedDesirePostion();

	void MoveRigt();
	void MoveLeft();
	void MoveUp();
	void MoveDown();

	list<Direction> Lee(MatPos startPos, MatPos finishPos);
	void PrintRouteMap(int mat[][50]);
	list<Direction> FindPath(int paths[][50], MatPos startPos, MatPos finishPos);
	void ShowPath(list<Direction> list);

	void Move(Direction dir);

	void GetFinishPosition(MatPos& pos);

	MatPos finishPos;
	MatPos startPos;
	list<Direction> directionPath;

	bool viz[50][50];
	int paths[50][50];

	World* world;

	bool move;
	bool isStaying;

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

