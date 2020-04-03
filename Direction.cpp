#include "Direction.h"


Direction GetRandomDirection()
{
	int dir = rand() % 4;

	switch (dir)
	{
	case 0: // direction will be Up
		return Direction::UP;

	case 1: // direction will be Right
		return Direction::RIGHT;

	case 2: // direction will be Down
		return Direction::DOWN;

	case 3: // direction will be Left
		return Direction::LEFT;
	}
}