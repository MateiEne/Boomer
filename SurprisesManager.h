#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Constants/Constants.h"
#include "MatPos.h"
#include "Animation.h"
#include "World.h"
#include "MathUtils.h" 
#include "SurpriseType.h"

using namespace std;

class SurprisesManager
{
public:
	SurprisesManager(World* world, const char* texture);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	bool IsCellRandomSurprise(MatPos pos);
	bool IsCellRandomSurprise(int l, int c);
	bool IsCellRandomSurprise(sf::Vector2f worldPos);

	bool IsCellBombsSupplySurprise(MatPos pos);
	bool IsCellBombsSupplySurprise(sf::Vector2f worldPos);

	bool IsCellASurprise(sf::Vector2f worldPos);

	void RemoveSurpriseFromMap(MatPos pos);
	void RemoveSurpriseFromMap(int l, int c);
	void RemoveSurpriseFromMap(sf::Vector2f pos);

	SurpriseType GetSurprise(sf::Vector2f worldPos);

	void PrintSurpriseMap();

private:
	void InitSurpriseMap();
	void InitSprite(sf::Sprite& sprite, MatPos worldPos);
	void InitSprite();
	void GenerateSurprises();

	World* world;

	sf::Texture texture;
	sf::Sprite  randomSurpriseSprite;
	sf::Sprite	bombSupplySurpriseSprite;

	MatPos surpriseMatPos;
	sf::Vector2f position;

	SurpriseType surpriseMap[50][50];
};

