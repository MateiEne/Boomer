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

	void Update(float dt);

private:
	void InitAnimation(Animation<sf::IntRect>& animation, const int count, const MatPos frames[]);
	bool IsSurrounded();

	void MoveRigt();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	void MoveRandom();
	
	void MoveRandomWithProbabilities();
	void Stay();

	void MoveRandomOrStay();

	bool isStaying;

	Animation<sf::IntRect> stayAnimation;
};

