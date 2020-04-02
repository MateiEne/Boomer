#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "Constants.h"
#include "MatPos.h"

using namespace std;

class World
{
public:
	 World(const char* fileName, const char* tilesTexture, vector<MatPos> playerPositions);
	~World();
	void Draw(sf::RenderWindow& window);
	bool IsCellEmpty(MatPos pos);
	bool IsCellEmpty(sf::Vector2f worldPos);

private:
	void ReadFromFIle(const char* fileName);
	void InitSprite(sf::Sprite& sprite, MatPos pos);
	void GenerateBoxes();
	void RemoveBoxesAroundPlayers(vector<MatPos> playersPosition);

	//Textures
	sf::Texture tilesTexture;
	
	//Sprites
	sf::Sprite wallSprite;
	sf::Sprite boxSprite;
	sf::Sprite floorSprite;

	char map[100][100];
};

