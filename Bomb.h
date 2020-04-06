#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Constants.h"
#include "Animation.h"

using namespace std;

class Bomb
{
public:
	Bomb(const char* bombTexture, const char* explosionTexture, MatPos pos);
	~Bomb();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

private:
	void InitBombSprite();
	void InitAnimation(
		Animation& animation, 
		const int count, 
		const MatPos frames[], 
		const float frameWidth, 
		const float frameHeight
	);
	void DrawSpriteAt(sf::RenderWindow& window, sf::Sprite& sprite, MatPos pos);
	void DrawExplosionFrame(sf::RenderWindow& window, MatPos pos, MatPos sheetPos);
	void DrawYSide(sf::RenderWindow& window, int length, bool up, int explosionIndex);
	void DrawXSide(sf::RenderWindow& window, int length, bool right, int explosionIndex);

	sf::Texture explosionTexture;
	sf::Texture bombTexture;

	sf::Sprite bombSprite;

	Animation fireAnimation;
	Animation explosionAnimation;

	MatPos matPos;

	bool exploted;
};

