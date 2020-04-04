#pragma once
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

enum class Direction
{
	RIGHT,
	LEFT,
	DOWN,
	UP
};

namespace DirectionsUtils
{
	Direction GetRandomDirection();
	Direction GetOppositeDirection(Direction dir);
	vector<Direction> GetSideDirection(Direction dir);
	vector<Direction> ShuffleDirections();
}