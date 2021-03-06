#include "DeadWalker.h"

using namespace PlayerConst;
using namespace DeadWalkerConst;

DeadWalker::DeadWalker(World* world, SurprisesManager* surpriseManager, const char* texture, MatPos pos, string name) :
	BasePlayer(world, surpriseManager, texture, pos, name),
	shadows(DeadWalkerConst::Shadow::COUNT, DeadWalkerConst::Shadow::RECORD_TIME)
{
	srand(time(NULL));

	stayCounter = 0;

	MatPos startPos = GetStartPosition();

	cout << startPos;

	SetPosition(startPos);
}

DeadWalker::~DeadWalker()
{
}

void DeadWalker::Stay()
{
	BasePlayer::Stay();

	stayCounter = 0;
}

MatPos DeadWalker::GetStartPosition()
{
	/*
		the reason why we put the deadWalker in a box, is that we want him to be generate like a 
		"surprise", and be able to walk only when the box is destroied
	*/

	MatPos resultPos;

	resultPos.l = rand() % (WorldConst::NL);
	resultPos.c = rand() % (WorldConst::NC);

	while (!world->IsCellBox(resultPos))
	{
		resultPos.l = rand() % (WorldConst::NL);
		resultPos.c = rand() % (WorldConst::NC);
	}

	return resultPos;
}

void DeadWalker::SetPosition(MatPos pos)
{
	position.x = pos.c * WorldConst::CELL_WIDTH;
	position.y = pos.l * WorldConst::CELL_HEIGHT;
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

void DeadWalker::UpdateShadows(float dt)
{
	shadows.Update(dt);
	if (shadows.ShouldAddRecord())
	{
		shadows.AddRecord(SpritePos(position, animation->GetCurrentFrame()));
	}
}

void DeadWalker::Update(float dt)
{
	if (world->IsCellBox(position))
	{
		return;
	}

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

	UpdateShadows(dt);

	BasePlayer::Update(dt);
}

void DeadWalker::DrawShadows(DrawManager& drawManager)
{
	deque<SpritePos> records = shadows.GetRecords();

	for (int i = 0; i < records.size(); i++)
	{
		if (records[i].position == position)
		{
			continue;
		}

		sprite.setPosition(records[i].position + sf::Vector2f(0, -WorldConst::BASE_GROUND));
		sprite.setTextureRect(records[i].frame);
		sprite.setColor(
			sf::Color(
				DeadWalkerConst::COLOR.r,
				DeadWalkerConst::COLOR.g,
				DeadWalkerConst::COLOR.b,
				i * DeadWalkerConst::Shadow::STEP_ALPHA + DeadWalkerConst::Shadow::BASE_ALPHA
			)
		);
		drawManager.Draw(sprite, Layer::FRONT);
	}

	sprite.setColor(DeadWalkerConst::COLOR);
}

void DeadWalker::Draw(DrawManager& drawManager)
{
	if (world->IsCellBox(position))
	{
		return;
	}
  
	DrawShadows(drawManager);

	BasePlayer::Draw(drawManager);
}