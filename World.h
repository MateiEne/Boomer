#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "Constants.h"
#include "MatPos.h"
#include "MazeGenerator.h"

using namespace std;

class World
{
public:
	 World(const char* fileName, const char* tilesTexture, vector<MatPos> playerPositions);
	~World();
	void Draw(sf::RenderWindow& window);
	void PrintMap();
	bool IsCellEmpty(MatPos pos);
	bool IsCellEmpty(int l, int c);
	bool IsCellEmpty(sf::Vector2f worldPos);
	void Restart(vector<MatPos> playerPositions);

private:
	void ReadFromFile(const char* fileName);
	void InitSprite(sf::Sprite& sprite, MatPos pos);
	void GenerateBoxes();
	void RemoveBoxesAroundPlayers(vector<MatPos> playersPosition);

	MazeGenerator mazeGenerator;

	//Textures
	sf::Texture tilesTexture;
	
	//Sprites
	sf::Sprite wallSprite;
	sf::Sprite boxSprite;
	sf::Sprite floorSprite;

	char map[50][50];
};

