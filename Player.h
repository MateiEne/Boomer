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

private:
	void InitSprite();
	void InitDownAnimation();


	//Textures
	sf::Texture spriteSheetTexture;

	//Sprites
	sf::Sprite sprite;

	sf::Vector2f position;
	
	Animation downAnimation;
};

