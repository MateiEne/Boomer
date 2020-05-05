#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Constants.h"
#include "MatPos.h"
#include "Animation.h"
#include "World.h"
#include "MathUtils.h" 

using namespace std;

class SurprisesManager
{
public:
	SurprisesManager(World* world, const char* texture, const char* fileName);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	bool IsCellRandomSurprise(MatPos pos);
	bool IsCellRandomSurprise(int l, int c);
	bool IsCellRandomSurprise(sf::Vector2f worldPos);

	bool IsCellBombsSupplySurprise(MatPos pos);
	bool IsCellBombsSupplySurprise(sf::Vector2f worldPos);

	void RemoveSurpriseFromMap(MatPos pos);
	void RemoveSurpriseFromMap(int l, int c);

	void PrintSurpriseMap();

private:
	void InitSurpriseMap();
	void ReadFromFile(const char* fileName);
	void InitSprite(sf::Sprite& sprite, MatPos pos);
	void InitSprite();
	void GenerateSurprises();

	World* world;

	sf::Texture texture;
	sf::Sprite  randomSurpriseSprite;
	sf::Sprite	bombSupplySurpriseSprite;

	MatPos surpriseMatPos;
	sf::Vector2f position;

	char surpriseMap[50][50];
};

