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
	Bomb(const char* bombTexture, const char* explosionTexture, MatPos pos, int length);
	~Bomb();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

private:
	void InitBombSprite();
	void InitAnimation(
		Animation<sf::IntRect>& animation,
		const int count, 
		const MatPos frames[], 
		const float frameWidth, 
		const float frameHeight
	);
	void InitExplosionAnimation();
	void InitLengthAnimation();
	void StartExplodeAnimation();
	void StartIncreaseLengthAnimation();
	void StartPeakLengthAnimation();
	void StartDecreaseLengthAnimation();
	bool ShouldDrawExplosion();
	void DrawSpriteAt(sf::RenderWindow& window, sf::Sprite& sprite, MatPos pos);
	void DrawExplosionFrame(sf::RenderWindow& window, MatPos pos, MatPos sheetPos);
	void DrawYSide(sf::RenderWindow& window, bool up, int length, int explosionIndex);
	void DrawXSide(sf::RenderWindow& window, bool right, int length, int explosionIndex);

	sf::Texture explosionTexture;
	sf::Texture bombTexture;

	sf::Sprite bombSprite;

	Animation<sf::IntRect> fireAnimation;
	Animation<int> explosionAnimation;

	Animation<int> increaseLengthAnimation;
	Animation<int> decreaseLengthAnimation;
	Animation<int> peakLengthAnimation;
	Animation<int>* currentLengthAnimation;

	MatPos matPos;

	int length;

	bool exploded;
	bool peakAnimationStarted;
	bool decreaseAnimationStarted;
};

