#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Constants.h"

using namespace std;

class Bomb
{
public:
	Bomb();
	~Bomb();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

private:
	vector<sf::Texture> textures;
	vector<sf::Sprite> sprites;

	sf::Vector2f position;

	float timeCounter;
	int currentFrame;
};

