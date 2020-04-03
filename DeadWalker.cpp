#include "DeadWalker.h"

using namespace PlayerConst;

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
	ChangeAnimation(rightAnimation);

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
	ChangeAnimation(leftAnimation);

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
	ChangeAnimation(downAnimation);

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
	ChangeAnimation(upAnimation);

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

void DeadWalker::ChangeAnimation(Animation& animation, bool loop)
{
	if (this->animation == &animation && this->animation->IsPlaying())
	{
		return;
	}

	this->animation = &animation;
	this->animation->Start(SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT, loop);
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

void DeadWalker::RandomizeDirection()
{
	auto dir = GetRandomDirection();

	switch (dir)
	{
	case Direction::RIGHT:
		MoveRigt();
		break;

	case Direction::LEFT:
		MoveLeft();
		break;

	case Direction::DOWN:
		MoveDown();
		break;

	case Direction::UP:
		MoveUp();
		break;
	}
}

void DeadWalker::Update(float dt)
{
	if (ReachedDesirePostion())
	{
		RandomizeDirection();
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
				desirePosition.x = position.x;
				move = false;
			}
			break;

		case Direction::LEFT:
			position.x -= SPEED * dt;
			if (position.x <= desirePosition.x)
			{
				desirePosition.x = position.x;
				move = false;
			}
			break;

		case Direction::DOWN:
			position.y += SPEED * dt;
			if (position.y >= desirePosition.y)
			{
				desirePosition.y = position.y;
				move = false;
			}
			break;

		case Direction::UP:
			position.y -= SPEED * dt;
			if (position.y <= desirePosition.y)
			{
				desirePosition.y = position.y;
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