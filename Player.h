#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"
#include "MatPos.h"
#include "Animation.h"

using namespace std;

class Player
{
public:
	Player(const char* texture, MatPos pos);
	~Player();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

private:
	void InitSprite();
	void InitAnimation(Animation& animation, int frames, int l);
	void ChangeAnimation(Animation animation);

	//Textures
	sf::Texture spriteSheetTexture;

	//Sprites
	sf::Sprite sprite;

	sf::Vector2f position;

	Animation animation;
	
	Animation downAnimation;
	Animation upAnimation;
	Animation rightAnimation;
	Animation leftAnimation;
};

