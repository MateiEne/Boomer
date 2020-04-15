#include "DeadWalker.h"

using namespace PlayerConst;
using namespace DeadWalkerConst;

DeadWalker::DeadWalker(World* world, const char* texture, MatPos pos) :
	downAnimation{ SpriteSheet::Move::TAG },
	upAnimation{ SpriteSheet::Move::TAG },
	rightAnimation{ SpriteSheet::Move::TAG },
	leftAnimation{ SpriteSheet::Move::TAG },
	stayAnimation{ SpriteSheet::Stay::TAG }
{
	srand(time(NULL));

	if (!spriteSheetTexture.loadFromFile(texture))
	{		
			cout << "error loading player spriteSheetTexture";
			exit(-1);
	}

	this->world = world;

	position.x = pos.c * WorldConst::CELL_WIDTH;
	position.y = pos.l * WorldConst::CELL_HEIGHT;

	desirePosition = position;

	Init();

	animation = &rightAnimation;
	direction = Direction::RIGHT;

	isStaying = false;
}

DeadWalker::~DeadWalker()
{

}

void DeadWalker::Init()
{
	InitSprite();

	InitAnimation(rightAnimation, SpriteSheet::Move::Right::COUNT, SpriteSheet::Move::Right::LINE);
	InitAnimation(upAnimation, SpriteSheet::Move::Up::COUNT, SpriteSheet::Move::Up::LINE);
	InitAnimation(downAnimation, SpriteSheet::Move::Down::COUNT, SpriteSheet::Move::Down::LINE);
	InitAnimation(leftAnimation, SpriteSheet::Move::Left::COUNT, SpriteSheet::Move::Left::LINE);
	InitAnimation(stayAnimation, SpriteSheet::Stay::COUNT, SpriteSheet::Stay::FRAMES);
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

void DeadWalker::InitSprite()
{
	sprite.setTexture(spriteSheetTexture);
	sprite.setTextureRect(
		sf::IntRect(
			SpriteSheet::DEFAULT_FRAME.c * SpriteSheet::FRAME_WIDTH,
			SpriteSheet::DEFAULT_FRAME.l * SpriteSheet::FRAME_HEIGHT,
			SpriteSheet::FRAME_WIDTH,
			SpriteSheet::FRAME_HEIGHT
		)
	);
	sprite.setScale(
		WorldConst::CELL_WIDTH / SpriteSheet::FRAME_WIDTH,
		WorldConst::CELL_HEIGHT / SpriteSheet::FRAME_HEIGHT
	);
}

void DeadWalker::InitAnimation(Animation<sf::IntRect>& animation, int count, int l)
{
	for (int i = 0; i < count; i++)
	{
		animation.AddFrame(
			sf::IntRect(
				i * SpriteSheet::FRAME_WIDTH,
				l * SpriteSheet::FRAME_HEIGHT,
				SpriteSheet::FRAME_WIDTH,
				SpriteSheet::FRAME_HEIGHT
			)
		);
	}
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

void DeadWalker::ChangeAnimation(Animation<sf::IntRect>& animation, float changeFrameTime, bool loop)
{
	if (this->animation == &animation && this->animation->IsPlaying())
	{
		return;
	}

	this->animation = &animation;
	this->animation->Start(changeFrameTime, loop);
}

void DeadWalker::ChangeAnimation(Animation<sf::IntRect>& animation, float changeFrameTime, float stayTime)
{
	if (this->animation == &animation && this->animation->IsPlaying())
	{
		return;
	}

	this->animation = &animation;
	this->animation->Start(changeFrameTime, stayTime);
}

bool DeadWalker::ReachedDesirePostion()
{
	return position == desirePosition;
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

bool DeadWalker::WillCollide(sf::Vector2f desirePosition)
{
	return world->IsCellBox(desirePosition) || world->IsCellWall(desirePosition);
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

	animation->Update(dt);
	if (move == true)
	{
		switch (direction)
		{
		case Direction::RIGHT:
			position.x += SPEED * dt;
			if (position.x >= desirePosition.x)
			{
				position.x = desirePosition.x;
				move = false;
			}
			break;

		case Direction::LEFT:
			position.x -= SPEED * dt;
			if (position.x <= desirePosition.x)
			{
				position.x = desirePosition.x;
				move = false;
			}
			break;

		case Direction::DOWN:
			position.y += SPEED * dt;
			if (position.y >= desirePosition.y)
			{
				position.y = desirePosition.y;
				move = false;
			}
			break;

		case Direction::UP:
			position.y -= SPEED * dt;
			if (position.y <= desirePosition.y)
			{
				position.y = desirePosition.y;
				move = false;
			}
			break;
		}
	}
	else if (animation->Is(SpriteSheet::Move::TAG))
	{
		animation->Stop();
	}
}

void DeadWalker::Draw(sf::RenderWindow& window)
{

	sprite.setPosition(position);
	sprite.setTextureRect(animation->GetCurrentFrame());
	window.draw(sprite);
}