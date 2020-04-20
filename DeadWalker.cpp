#include "DeadWalker.h"

using namespace PlayerConst;
using namespace DeadWalkerConst;

DeadWalker::DeadWalker(World* world, const char* texture, MatPos pos, string name) :
	BasePlayer(world, texture, pos, name),
	stayAnimation{ SpriteSheet::Stay::TAG }
{
	srand(time(NULL));

	InitAnimation(stayAnimation, SpriteSheet::Stay::COUNT, SpriteSheet::Stay::FRAMES);
	isStaying = false;
}

DeadWalker::~DeadWalker()
{
}

void DeadWalker::InitAnimation(Animation<sf::IntRect>& animation, const int count, const MatPos frames[])
{
	for (int i = 0; i < count; i++)
	{
		animation.AddFrame(
			sf::IntRect(
				frames[i].c * SpriteSheet::FRAME_WIDTH,
				frames[i].l * SpriteSheet::FRAME_HEIGHT,
				SpriteSheet::FRAME_WIDTH,
				SpriteSheet::FRAME_HEIGHT
			)
		);
	}
}


void DeadWalker::MoveRigt()
{
	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		return;
	}
	move = true;

	desirePosition = position;
	desirePosition.x += WorldConst::CELL_WIDTH;
	direction = Direction::RIGHT;
	ChangeAnimation(rightAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);

}

void DeadWalker::MoveLeft()
{
	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		return;
	}
	move = true;

	desirePosition = position;
	desirePosition.x -= WorldConst::CELL_WIDTH;
	direction = Direction::LEFT;
	ChangeAnimation(leftAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);

}

void DeadWalker::MoveDown()
{
	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		return;
	}
	move = true;

	desirePosition = position;
	desirePosition.y += WorldConst::CELL_HEIGHT;
	direction = Direction::DOWN;
	ChangeAnimation(downAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);

}

void DeadWalker::MoveUp()
{
	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		return;
	}
	move = true;

	desirePosition = position;
	desirePosition.y -= WorldConst::CELL_HEIGHT;
	direction = Direction::UP;
	ChangeAnimation(upAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);

}

void DeadWalker::Stay()
{
	ChangeAnimation(stayAnimation, SpriteSheet::Stay::TIME_FRAME_CHANGE_COUNT, DeadWalkerConst::STAY_TIME);
	isStaying = true;
	move = false;
}

bool DeadWalker::IsSurrounded()
{
	sf::Vector2f result;

	result.x = position.x + WorldConst::CELL_WIDTH;
	result.y = position.y;
	if (!WillCollide(result))
	{
		return false;
	}
	
	result.x = position.x - WorldConst::CELL_WIDTH;
	result.y = position.y;
	if (!WillCollide(result))
	{
		return false;
	}

	result.x = position.x;
	result.y = position.y + WorldConst::CELL_HEIGHT;
	if (!WillCollide(result))
	{
		return false;
	}

	result.x = position.x;
	result.y = position.y - WorldConst::CELL_HEIGHT;
	if (!WillCollide(result))
	{
		return false;
	}

	return true;
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
				MoveRigt();
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
				MoveRigt();
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

void DeadWalker::Update(float dt)
{
	if (ReachedDesirePostion())
	{
		if (isStaying)
		{
			if (!animation->IsPlaying())
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