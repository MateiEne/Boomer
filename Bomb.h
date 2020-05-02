#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Constants\Constants.h"
#include "Animation.h"
#include "World.h"

using namespace std;

class Bomb
{
public:
	Bomb(World* world, const char* bombFireTexture, const char* bombExplosionTexture, const char* explosionBodyTexture);
	~Bomb();

	void Fire(MatPos pos, int lenght);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	bool HasEnded();
	MatPos GetMatPosition();

private:
	void InitBombFireAnimation();
	void InitBombExplosionAnimation();
	void InitExplosionBodyAnimation();
	void InitLengthAnimation();

	void StartExplodeAnimation();
	void StartIncreaseLengthAnimation();
	void StartPeakLengthAnimation();
	void StartDecreaseLengthAnimation();

	bool ShouldDrawExplosion();
	void DrawBomb(sf::RenderWindow& window);
	void DrawSpriteAt(sf::RenderWindow& window, sf::Sprite& sprite, MatPos pos);
	void DrawExplosionFrame(sf::RenderWindow& window, MatPos pos, MatPos sheetPos);
	void DrawYSide(sf::RenderWindow& window, bool up, int lenght, int explosionIndex);
	void DrawXSide(sf::RenderWindow& window, bool right, int lenght, int explosionIndex);
	void DrawXPeak(sf::RenderWindow& window, bool right, MatPos pos, int explosionIndex);
	void DrawYPeak(sf::RenderWindow& window, bool up, MatPos pos, int explosionIndex);

	void MarkExplosionInMap(int lenght);
	void MarkExplosionDangerInMap(int lenght);
	void RemoveExplosionInMap(int lenght);
	void RemoveBoxesInMap();
	void MarkExplosionXSideInMap(int lenght, bool right, char ch);
	void MarkExplosionYSideInMap(int lenght, bool up, char ch);


	sf::Texture bombFireTexture;
	sf::Texture bombExplosionTexture;
	sf::Texture explosionBodyTexture;

	sf::Sprite bombSprite;

	Animation<sf::IntRect> bombFireAnimation;
	Animation<sf::IntRect> bombExplosionAnimation;
	Animation<int> explosionBodyAnimation;

	Animation<int> increaseLengthAnimation;
	Animation<int> decreaseLengthAnimation;
	Animation<int> peakLengthAnimation;
	Animation<int>* currentLengthAnimation;

	World* world;

	MatPos matPos;

	int lenght;

	bool finished;

	bool exploded;
	bool peakAnimationStarted;
	bool decreaseAnimationStarted;

	list<MatPos> boxesToRemove;
};

