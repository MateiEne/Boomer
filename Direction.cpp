#include "Direction.h"

Direction DirectionsUtils::GetRandomDirection()
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

vector<Direction> DirectionsUtils::ShuffleDirections()
{
	vector<Direction> result{ Direction::DOWN, Direction::LEFT, Direction::RIGHT, Direction::UP };

	auto seed = chrono::system_clock::now().time_since_epoch().count();

	shuffle(result.begin(), result.end(), default_random_engine(seed));

	return result;
}

Direction DirectionsUtils::GetOppositeDirection(Direction dir)
{

	switch (dir)
	{
	case Direction::RIGHT:
		return Direction::LEFT;

	case Direction::LEFT:
		return Direction::RIGHT;

	case Direction::DOWN:
		return Direction::UP;

	case Direction::UP:
		return Direction::DOWN;
	}
}

vector<Direction> DirectionsUtils::GetSideDirection(Direction dir)
{
	switch (dir)
	{
	case Direction::RIGHT:
		return vector<Direction> { Direction::UP, Direction::DOWN} ;

	case Direction::LEFT:
		return vector<Direction> { Direction::UP, Direction::DOWN};

	case Direction::UP:
		return vector<Direction> { Direction::RIGHT, Direction::LEFT};

	case Direction::DOWN:
		return vector<Direction> { Direction::RIGHT, Direction::LEFT };
	}
}
