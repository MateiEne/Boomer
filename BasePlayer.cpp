#include "BasePlayer.h"

using namespace PlayerConst;

BasePlayer::BasePlayer(World* world, BombsManager* bombsManager, const char* texture, MatPos pos, string name) :
	downAnimation{ SpriteSheet::Move::TAG },
	upAnimation{ SpriteSheet::Move::TAG },
	rightAnimation{ SpriteSheet::Move::TAG },
	leftAnimation{ SpriteSheet::Move::TAG },
	putBombDownAnimation{ SpriteSheet::PutBomb::TAG },
	putBombLeftAnimation{ SpriteSheet::PutBomb::TAG },
	putBombRightAnimation{ SpriteSheet::PutBomb::TAG },
	putBombUpAnimation{ SpriteSheet::PutBomb::TAG }
{
	if (!spriteSheetTexture.loadFromFile(texture))
	{
		cout << "error loading player spriteSheetTexture";
		exit(-1);
	}

	InitSprite();

	this->world = world;

	this->name = name;

	this->bombsManager = bombsManager;

	position.x = pos.c * WorldConst::CELL_WIDTH;
	position.y = pos.l * WorldConst::CELL_HEIGHT;

	desirePosition = position;

	InitAnimations();

	animation = &downAnimation;
	prevAnimation = animation;

	move = false;
	putBomb = false;
	direction = Direction::DOWN;
}

void BasePlayer::InitSprite()
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

void BasePlayer::InitAnimations()
{
	InitAnimation(rightAnimation, SpriteSheet::Move::Right::COUNT, SpriteSheet::Move::Right::LINE);
	InitAnimation(upAnimation, SpriteSheet::Move::Up::COUNT, SpriteSheet::Move::Up::LINE);
	InitAnimation(downAnimation, SpriteSheet::Move::Down::COUNT, SpriteSheet::Move::Down::LINE);
	InitAnimation(leftAnimation, SpriteSheet::Move::Left::COUNT, SpriteSheet::Move::Left::LINE);

	InitAnimation(
		putBombDownAnimation,
		SpriteSheet::PutBomb::Down::COUNT,
		SpriteSheet::PutBomb::Down::LINE,
		SpriteSheet::PutBomb::Down::FRAMES
	);
	InitAnimation(
		putBombRightAnimation,
		SpriteSheet::PutBomb::Right::COUNT,
		SpriteSheet::PutBomb::Right::LINE,
		SpriteSheet::PutBomb::Right::FRAMES
	);
	InitAnimation(putBombLeftAnimation,
		SpriteSheet::PutBomb::Left::COUNT,
		SpriteSheet::PutBomb::Left::LINE,
		SpriteSheet::PutBomb::Left::FRAMES
	);
	InitAnimation(
		putBombUpAnimation,
		SpriteSheet::PutBomb::Up::COUNT,
		SpriteSheet::PutBomb::Up::LINE,
		SpriteSheet::PutBomb::Up::FRAMES
	);

	/*InitTurnAnimation(
		turnLeftAnimation,
		SpriteSheet::Move::Down::DEFAULT_FRAME,
		SpriteSheet::Move::Down::LINE,
		SpriteSheet::Move::Left::DEFAULT_FRAME,
		SpriteSheet::Move::Left::LINE
	);
	InitTurnAnimation(
		turnRightAnimation,
		SpriteSheet::Move::Down::DEFAULT_FRAME,
		SpriteSheet::Move::Down::LINE,
		SpriteSheet::Move::Right::DEFAULT_FRAME,
		SpriteSheet::Move::Right::LINE
	);
	InitTurnAnimation(
		turnUpAnimation,
		SpriteSheet::Move::Right::DEFAULT_FRAME,
		SpriteSheet::Move::Right::LINE,
		SpriteSheet::Move::Up::DEFAULT_FRAME,
		SpriteSheet::Move::Up::LINE
	);
	InitTurnAnimation(
		turnDownAnimation,
		SpriteSheet::Move::Right::DEFAULT_FRAME,
		SpriteSheet::Move::Right::LINE,
		SpriteSheet::Move::Down::DEFAULT_FRAME,
		SpriteSheet::Move::Down::LINE
	);*/
}

void BasePlayer::InitAnimation(Animation<sf::IntRect>& animation, int count, int l)
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

void BasePlayer::InitAnimation(Animation<sf::IntRect>& animation, const int count, const int l, const int frames[])
{
	for (int i = 0; i < count; i++)
	{
		animation.AddFrame(
			sf::IntRect(
				frames[i] * SpriteSheet::FRAME_WIDTH,
				l * SpriteSheet::FRAME_HEIGHT,
				SpriteSheet::FRAME_WIDTH,
				SpriteSheet::FRAME_HEIGHT
			)
		);
	}
}

void BasePlayer::InitTurnAnimation(
	Animation<sf::IntRect>& animation,
	int defaultFirstPosC,
	int defaultFirstPosL,
	int defaultSecondPosC,
	int defaultSecondPosL
)
{
	animation.AddFrame(
		sf::IntRect(
			defaultFirstPosC * SpriteSheet::FRAME_WIDTH,
			defaultFirstPosL * SpriteSheet::FRAME_HEIGHT,
			SpriteSheet::FRAME_WIDTH,
			SpriteSheet::FRAME_HEIGHT
		)
	);
	animation.AddFrame(
		sf::IntRect(
			defaultSecondPosC * SpriteSheet::FRAME_WIDTH,
			defaultSecondPosL * SpriteSheet::FRAME_HEIGHT,
			SpriteSheet::FRAME_WIDTH,
			SpriteSheet::FRAME_HEIGHT
		)
	);
}

void BasePlayer::ChangeAnimation(Animation<sf::IntRect>& animation, float changeFrameTime, bool loop)
{
	if (this->animation == &animation && this->animation->IsPlaying())
	{
		return;
	}

	prevAnimation = this->animation;

	this->animation = &animation;
	this->animation->Start(changeFrameTime, loop);
}

MatPos BasePlayer::GetMatPlayerPosition()
{
	MatPos playerPos;

	playerPos.l = position.y / WorldConst::CELL_HEIGHT;
	playerPos.c = position.x / WorldConst::CELL_WIDTH;

	return playerPos;
}

bool BasePlayer::CanMove()
{
	// player can move if he doesn't have to put a bomb
	return putBomb == false;
}

bool BasePlayer::CanPutBomb()
{
	return world->IsCellEmpty(position) && bombsManager->CanPutBomb(name, BOMB_COUNT);
}

void BasePlayer::PutBomb()
{
	if (!CanPutBomb())
	{
		return;
	}

	putBomb = true;
}

bool BasePlayer::WillCollide(sf::Vector2f desirePosition)
{
	return world->IsCellBox(desirePosition) || world->IsCellWall(desirePosition);
}

bool BasePlayer::ReachedDesirePostion()
{
	return position == desirePosition;
}

void BasePlayer::FireBomb()
{
	MatPos playerPos = GetMatPlayerPosition();

	bombsManager->PutBomb(playerPos, BOMB_LENGTH, name);
}

void BasePlayer::UpdateMovement(float dt)
{
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

void BasePlayer::UpdatePutBomb()
{
	if (putBomb && ReachedDesirePostion())
	{
		if (!animation->Is(SpriteSheet::PutBomb::TAG))
		{
			switch (direction)
			{
			case Direction::RIGHT:
				ChangeAnimation(putBombRightAnimation, SpriteSheet::PutBomb::TIME_FRAME_CHANGE_COUNT, false);
				break;

			case Direction::LEFT:
				ChangeAnimation(putBombLeftAnimation, SpriteSheet::PutBomb::TIME_FRAME_CHANGE_COUNT, false);
				break;

			case Direction::DOWN:
				ChangeAnimation(putBombDownAnimation, SpriteSheet::PutBomb::TIME_FRAME_CHANGE_COUNT, false);
				break;

			case Direction::UP:
				ChangeAnimation(putBombUpAnimation, SpriteSheet::PutBomb::TIME_FRAME_CHANGE_COUNT, false);
				break;
			}
		}
		else
		{
			// putBomb aniumation is playing
			if (!animation->IsPlaying())
			{
				FireBomb();
				putBomb = false;
				animation = prevAnimation;
			}
		}
	}
}

void BasePlayer::Update(float dt)
{
	animation->Update(dt);

	UpdateMovement(dt);

	UpdatePutBomb();
}

void BasePlayer::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setTextureRect(animation->GetCurrentFrame());
	window.draw(sprite);
}