#include "Direction.h"

vector<Direction> ShuffleDirections()
{
	vector<Direction> result{ Direction::DOWN, Direction::LEFT, Direction::UP, Direction::RIGHT };

	auto seed = chrono::system_clock::now().time_since_epoch().count();

	shuffle(result.begin(), result.end(), default_random_engine(seed));

	return result;
}