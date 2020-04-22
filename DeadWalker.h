#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Constants.h"
#include "MatPos.h"
#include "Animation.h"
#include "Direction.h"
#include "World.h"
#include "MathUtils.h" 
#include "BasePlayer.h"

using namespace std;

class DeadWalker : public BasePlayer
{
public:
	DeadWalker(World* world, const char* texture, MatPos pos, string name);
	~DeadWalker();

	void Stay();

	void Update(float dt);

private:
	bool IsSurrounded();
	void MoveRandom();
	
	void MoveRandomWithProbabilities();

	void MoveRandomOrStay();

	float stayCounter;
};

