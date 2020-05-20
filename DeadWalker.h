#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Constants/Constants.h"
#include "DrawManager.h"
#include "MatPos.h"
#include "Animation.h"
#include "Direction.h"
#include "World.h"
#include "MathUtils.h" 
#include "BasePlayer.h"
#include "SpritePos.h"
#include "History.h"
#include "SurprisesManager.h"

using namespace std;

class DeadWalker : public BasePlayer
{
public:
	DeadWalker(World* world, SurprisesManager* surpriseManager, const char* texture, MatPos pos, string name);
	~DeadWalker();

	void Stay();

	void Update(float dt);
	void Draw(DrawManager& drawManager);

protected:
	void OnLifeLost();

private:
	void SetPosition(MatPos pos);
	MatPos GetStartPosition();
	void MoveRandom();
	void MoveRandomWithProbabilities();
	void MoveRandomOrStay();

	void UpdateShadows(float dt);
	void DrawShadows(DrawManager& drawManager);

	History<SpritePos> shadows;

	float stayCounter;
};

