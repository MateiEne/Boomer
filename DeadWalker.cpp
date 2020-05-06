#include "DeadWalker.h"

using namespace PlayerConst;
using namespace DeadWalkerConst;

DeadWalker::DeadWalker(World* world, SurprisesManager* surpriseManager, const char* texture, MatPos pos, string name) :
	stayCounter{ 0 },
	BasePlayer(world, surpriseManager, texture, pos, name)
{
	srand(time(NULL));
}

DeadWalker::~DeadWalker()
{
}

void DeadWalker::Stay()
{
	BasePlayer::Stay();

	stayCounter = 0;
}

void DeadWalker::MoveRandom()
{
	vector<Direction> directions = DirectionsUtils::ShuffleDirections();

	for (Direction direction : directions)
	{
		sf::Vector2f futurePosition = position;

		switch (direction)
		{
		case Direction::RIGHT:
			futurePosition.x += WorldConst::CELL_WIDTH;
			if (!WillCollide(futurePosition))
			{
				MoveRight();
				return;
			}
			break;

		case Direction::LEFT:
			futurePosition.x -= WorldConst::CELL_WIDTH;
			if (!WillCollide(futurePosition))
			{
				MoveLeft();
				return;
			}
			break;

		case Direction::DOWN:
			futurePosition.y += WorldConst::CELL_HEIGHT;
			if (!WillCollide(futurePosition))
			{
				MoveDown();
				return;
			}
			break;

		case Direction::UP:
			futurePosition.y -= WorldConst::CELL_HEIGHT;
			if (!WillCollide(futurePosition))
			{
				MoveUp();
				return;
			}
			break;
		}

	}
}

void DeadWalker::MoveRandomWithProbabilities()
{
	Direction initialDirection = direction;

	for (;;)
	{
		// will break the infinte for when the chosen direction will corespund to an empty cell 

		vector<float> weights{ DirectionsProbability::OPPOSITE, DirectionsProbability::SIDE, DirectionsProbability::SAME };
		int index = MathUtils::GetRandomDiscreteDistribution(weights);

		if (index == 0)	// the OPPOSITE direction has been chosen
		{
			direction = DirectionsUtils::GetOppositeDirection(direction);
		}
		else if (index == 1)	// the SIDE direction has been chosen
		{
			vector<Direction> sideDirections = DirectionsUtils::GetSideDirection(direction);
			int sideDirectionChoice = rand() % sideDirections.size();

			direction = sideDirections[sideDirectionChoice];
		}

		sf::Vector2f futurePosition = position;

		switch (direction)
		{
		case Direction::RIGHT:
			futurePosition.x += WorldConst::CELL_WIDTH;
			if (!WillCollide(futurePosition))
			{
				MoveRight();
				return;
			}
			break;

		case Direction::LEFT:
			futurePosition.x -= WorldConst::CELL_WIDTH;
			if (!WillCollide(futurePosition))
			{
				MoveLeft();
				return;
			}
			break;

		case Direction::DOWN:
			futurePosition.y += WorldConst::CELL_HEIGHT;
			if (!WillCollide(futurePosition))
			{
				MoveDown();
				return;
			}
			break;

		case Direction::UP:
			futurePosition.y -= WorldConst::CELL_HEIGHT;
			if (!WillCollide(futurePosition))
			{
				MoveUp();
				return;
			}
			break;
		}

		// reset the direction with the initial one
		direction = initialDirection;
	}
}

void DeadWalker::MoveRandomOrStay()
{
	if (IsSurrounded())
	{
		Stay();
		return;
	}

	float choice = (float)rand() / (float)RAND_MAX;
	
	if (choice < STAY_PROBABILITY)
	{
		Stay();
	}
	else
	{
		MoveRandomWithProbabilities();
	}
}

void DeadWalker::OnLifeLost()
{
	return;
}

void DeadWalker::Update(float dt)
{
	if (IsInGoodMatPosition())
	{
		if (isStaying)
		{
			stayCounter += dt;
			if (stayCounter >= DeadWalkerConst::STAY_TIME)
			{
				isStaying = false;
			}
		}
		else
		{
			MoveRandomOrStay();
		}
	}

	BasePlayer::Update(dt);
}