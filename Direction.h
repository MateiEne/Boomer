#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <chrono>

using namespace std;

enum class Direction
{
	RIGHT,
	LEFT,
	DOWN,
	UP
};

vector<Direction> ShuffleDirections();