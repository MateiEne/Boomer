#pragma once

#include <iostream>

#include "World.h"
#include "Direction.h"
#include "Constants/Constants.h"
#include "SurprisesManager.h"
#include "Animation.h"
#include "DrawManager.h"

using namespace std;

class Arrow
{
public:
	Arrow(World* world, const char* texture);

	void InitSprite();
	sf::IntRect GetFrame(Direction dir);

	void Shoot(MatPos pos, Direction dir);

	void Update(float dt);
	void Draw(DrawManager& drawManager);

private:

	World* world;

	Direction direction;

	//Textures
	sf::Texture spriteSheetTexture;

	bool started;

	//Sprites
	sf::Sprite sprite;

	sf::IntRect frame;

	sf::Vector2f position;
	sf::Vector2f desirePosition;
};

