#pragma once
#include <stdlib.h>
#include <time.h>

enum class Direction
{
	RIGHT,
	LEFT,
	DOWN,
	UP
};

Direction GetRandomDirection();