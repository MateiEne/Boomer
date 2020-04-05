#include "Bomb.h"

Bomb::Bomb() :
	textures{ 23 },
	sprites{ 23 }
{

	int index = 0;

	for (int i = 1; i <= 4; i++)
	{
		char path[50];
		sprintf_s(path, "Assets\\Bomb\\drop%d.png", i);

		textures[index].loadFromFile(path);
		sprites[index].setTexture(textures[index]);

		sprites[index].setScale(
			WorldConst::CELL_WIDTH / 160,
			WorldConst::CELL_HEIGHT / 160
			);

		index++;
	}

	for (int i = 1; i <= 9; i++)
	{
		char path[50];
		sprintf_s(path, "Assets\\Bomb\\f%d.png", i);

		textures[index].loadFromFile(path);
		sprites[index].setTexture(textures[index]);

		sprites[index].setScale(
			WorldConst::CELL_WIDTH / 160,
			WorldConst::CELL_HEIGHT / 160
			);

		index++;
	}

	for (int i = 1; i <= 10; i++)
	{
		char path[50];
		sprintf_s(path, "Assets\\Bomb\\%d.png", i);

		textures[index].loadFromFile(path);
		sprites[index].setTexture(textures[index]);

		sprites[index].setScale(
			WorldConst::CELL_WIDTH / 160,
			WorldConst::CELL_HEIGHT / 160
			);

		index++;
	}

	position.y = 4 * WorldConst::CELL_HEIGHT;
	position.x = 4 * WorldConst::CELL_WIDTH;

	timeCounter = 0;
	currentFrame = 0;
}

Bomb::~Bomb()
{
}

void Bomb::Update(float dt)
{
	timeCounter += dt;

	if (timeCounter >= 0.07f)
	{
		timeCounter = 0;
		currentFrame++;
		if (currentFrame == sprites.size())
		{
			currentFrame = 0;
		}
	}
}

void Bomb::Draw(sf::RenderWindow& window)
{
	sprites[currentFrame].setPosition(position);
	window.draw(sprites[currentFrame]);
}
