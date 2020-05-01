#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>
#include <list>
#include <string>

#include "Constants.h"
#include "MatPos.h"
#include "Animation.h"
#include "Direction.h"
#include "World.h"
#include "BombsManager.h"
#include "BombPlayer.h"

class PlayerAI : public BombPlayer
{
public:
	PlayerAI(World* world, BombsManager* bombsManager, const char* texture, MatPos pos, string name);

	void Update(float dt);

private:
	list<Direction> Lee(MatPos startPos, MatPos finishPos);
	list<Direction> LeeToASafePosition(MatPos startPos);
	void PrintRouteMap(int mat[][50]);
	list<Direction> FindPath(int paths[][50], MatPos startPos, MatPos finishPos);
	void ShowPath(list<Direction> list);
	void MoveToASafePosition();
	bool IsInADangerPosition(MatPos pos);

	MatPos GetFinishPosition();
	MatPos GetStartPosition();

	list<Direction> directionPath;
};

