#include "DeadWalker.h"

using namespace PlayerConst;
using namespace DeadWalkerConst;

DeadWalker::DeadWalker(World& world, const char* texture, MatPos pos)
{
	srand(time(NULL));

	if (!spriteSheetTexture.loadFromFile(texture))
	{		
			cout << "error loading player spriteSheetTexture";
			exit(-1);
	}

	this->world = &world;

	position.x = pos.c * WorldConst::CELL_WIDTH;
	position.y = pos.l * WorldConst::CELL_HEIGHT;

	desirePosition = position;

	Init();

	animation = &rightAnimation;
	direction = Direction::RIGHT;
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
	ChangeAnimation(stayAnimation, SpriteSheet::Stay::TIME_FRAME_CHANGE_COUNT);
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

void DeadWalker::InitAnimation(Animation& animation, int count, int l)
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

void DeadWalker::InitAnimation(Animation& animation, const int count, const MatPos frames[])
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

void DeadWalker::ChangeAnimation(Animation& animation, float changeFrameTime, bool loop)
{
	if (this->animation == &animation && this->animation->IsPlaying())
	{
		return;
	}

	this->animation = &animation;
	this->animation->Start(changeFrameTime, loop);
}

bool DeadWalker::IsMoveAnimation()
{
	return animation == &rightAnimation ||
		animation == &leftAnimation ||
		animation == &upAnimation ||
		animation == &downAnimation;
}

bool DeadWalker::ReachedDesirePostion()
{
	return position == desirePosition;
}

bool DeadWalker::WillCollide(sf::Vector2f desirePosition)
{
	return !world->IsCellEmpty(desirePosition);
}

void DeadWalker::MoveRandom()
{
	vector<Direction> directions = ShuffleDirections();

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

void DeadWalker::MoveRandomOrStay()
{
	float choice = (float)rand() / (float)RAND_MAX;

	if (choice <= STAY_PROBABILITY)
	{
		Stay();
	}
	else
	{
		MoveRandom();
	}
}

void DeadWalker::Update(float dt)
{
	if (ReachedDesirePostion())
	{
		MoveRandomOrStay();
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
	else if (IsMoveAnimation())
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