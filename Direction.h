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

Direction GetRandomDirection();
vector<Direction> ShuffleDirections();