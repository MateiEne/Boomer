#include "Direction.h"


Direction GetRandomDirection()
{
	srand(time(NULL));

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

vector<Direction> ShuffleDirections()
{

	vector<Direction> result{ Direction::DOWN, Direction::LEFT, Direction::RIGHT, Direction::UP };

	shuffle(result.begin(), result.end(), default_random_engine(time(NULL)));

	return result;
}