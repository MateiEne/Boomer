#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <list>

#include "Constants/Constants.h"
#include "DrawManager.h"
#include "MatPos.h"
#include "MazeGenerator.h"

using namespace std;

class World
{
public:
	 World(const char* fileName, const char* tilesTexture, vector<MatPos> playerPositions);
	~World();
	void Draw(DrawManager& drawManager);
	void Update(float dt);

	void PrintMap();
	bool IsCellEmpty(MatPos pos);
	bool IsCellEmpty(int l, int c);
	bool IsCellEmpty(sf::Vector2f worldPos);

	bool IsCellWall(MatPos pos);
	bool IsCellWall(int l, int c);
	bool IsCellWall(sf::Vector2f worldPos);

	bool IsCellBox(MatPos pos);
	bool IsCellBox(int l, int c);
	bool IsCellBox(sf::Vector2f worldPos);

	bool CanPutBomb(sf::Vector2f worldPos);

	bool IsCellMarkedAsExplosionDanger(MatPos pos);
	bool IsCellMarkedAsExplosion(MatPos pos);
	bool IsCellMarkedAsExplosion(sf::Vector2f worldPos);
	bool IsCellBomb(MatPos pos);
	bool IsCellBomb(sf::Vector2f worldPos);

	void Restart(vector<MatPos> playerPositions);

	void PutBomb(MatPos pos);
	void MarkExplosionBody(MatPos pos, char ch);
	void RemoveExplosion(MatPos pos);

	void RemoveBomb(MatPos pos);

	void RemoveBox(MatPos pos);

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

