#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>

#include <stdlib.h>
#include <chrono>

using namespace std;

enum class Direction
{
	RIGHT,
	LEFT,
	DOWN,
	UP
};

inline ostream& operator << (ostream& os, const Direction& direction)
{
	switch (direction)
	{
	case Direction::RIGHT:
		os << "right";
		break;

	case Direction::LEFT:
		os << "left";
		break;

	case Direction::UP:
		os << "up";
		break;

	case Direction::DOWN:
		os << "down";
		break;
	}

	return os;
}

namespace DirectionsUtils
{
	Direction GetRandomDirection();
	Direction GetOppositeDirection(Direction dir);
	vector<Direction> GetSideDirection(Direction dir);
	vector<Direction> ShuffleDirections();
}