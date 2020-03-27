#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Player
{
public:
	Player(const char* texture);
	~Player();

	void Draw(sf::RenderWindow& window);

private:
	//Textures
	sf::Texture spriteSheetTexture;

	//Sprites
	sf::Sprite sprite;
};

