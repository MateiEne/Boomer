#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <set>

#include "Constants/Constants.h"
#include "DrawManager.h"
#include "Animation.h"
#include "World.h"

using namespace std;

class Bomb
{
public:
	Bomb(World* world, const char* bombFireTexture, const char* bombExplosionTexture, const char* explosionBodyTexture);
	~Bomb();

	void Fire(MatPos pos, int lenght);
	bool HasEnded();
	MatPos GetMatPosition();

	void Update(float dt);
	void Draw(DrawManager& drawManager);

private:
	void InitBombFireAnimation();
	void InitBombExplosionAnimation();
	void InitExplosionBodyAnimation();
	void InitLengthAnimation();

	void StartExplodeAnimation();
	void StartIncreaseLengthAnimation();
	void StartPeakLengthAnimation();
	void StartDecreaseLengthAnimation();

	void ManageLengthAnimations();

	bool ShouldDrawExplosion();
	void DrawBomb(DrawManager& drawManager);
	void DrawSpriteAt(DrawManager& drawManager, sf::Sprite& sprite, MatPos pos, sf::Vector2f scale);
	void DrawExplosionFrame(DrawManager& drawManager, MatPos pos, MatPos sheetPos, sf::Vector2f scale);
	void DrawYSide(DrawManager& drawManager, bool up, int lenght, int explosionIndex);
	void DrawXSide(DrawManager& drawManager, bool right, int lenght, int explosionIndex);
	void DrawXPeak(DrawManager& drawManager, bool right, MatPos pos, int explosionIndex);
	void DrawYPeak(DrawManager& drawManager, bool up, MatPos pos, int explosionIndex);

	void UpdateMapMark();
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

	set<MatPos> boxesToRemove;
	bool dangerMarkAdded;
	bool explosionMarkRemoved;
};

