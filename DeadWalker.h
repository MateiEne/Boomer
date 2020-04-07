#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

#include "Constants.h"
#include "MatPos.h"
#include "Animation.h"
#include "Direction.h"
#include "World.h"
#include "MathUtils.h" 

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
	void ChangeAnimation(Animation<sf::IntRect>& animation, float changeFrameTime, bool loop = true);
	void ChangeAnimation(Animation<sf::IntRect>& animation, float changeFrameTime, float stayTime);
	void InitAnimation(Animation<sf::IntRect>& animation, int count, int l);
	void InitAnimation(Animation<sf::IntRect>& animation, const int count, const MatPos frames[]);
	void Init();

	bool ReachedDesirePostion();
	bool IsSurrounded();

	void MoveRigt();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void MoveRandom();
	
	void MoveRandomWithProbabilities();
	void Stay();

	void MoveRandomOrStay();

	bool WillCollide(sf::Vector2f desirePosition);

	World* world;
	
	bool move;
	bool isStaying;

	//Textures
	sf::Texture spriteSheetTexture;

	//Sprites
	sf::Sprite sprite;


	sf::Vector2f position;
	sf::Vector2f desirePosition;

	Animation<sf::IntRect>* animation;
	Direction direction;

	Animation<sf::IntRect> downAnimation;
	Animation<sf::IntRect> upAnimation;
	Animation<sf::IntRect> rightAnimation;
	Animation<sf::IntRect> leftAnimation;
	Animation<sf::IntRect> stayAnimation;
};

