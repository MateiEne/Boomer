#include "BombPlayer.h"

using namespace PlayerConst;

BombPlayer::BombPlayer(World* world, BombsManager* bombsManager, const char* texture, MatPos pos, string name) :
	BasePlayer(world, texture, pos, name),
	putBombDownAnimation{ SpriteSheet::PutBomb::TAG },
	putBombLeftAnimation{ SpriteSheet::PutBomb::TAG },
	putBombRightAnimation{ SpriteSheet::PutBomb::TAG },
	putBombUpAnimation{ SpriteSheet::PutBomb::TAG }
{
	InitBombAnimations();

	this->bombsManager = bombsManager;

	putBomb = false;
}

void BombPlayer::InitBombAnimations()
{
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
}

void BombPlayer::InitAnimation(Animation<sf::IntRect>& animation, const int count, const int l, const int frames[])
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

bool BombPlayer::CanPutBomb()
{
	return world->IsCellEmpty(position) && bombsManager->CanPutBomb(name, BOMB_COUNT);
}

void BombPlayer::PutBomb()
{
	if (!CanPutBomb())
	{
		return;
	}

	putBomb = true;
}

void BombPlayer::FireBomb()
{
	MatPos playerPos = GetMatPlayerPosition();

	bombsManager->PutBomb(playerPos, BOMB_LENGTH, name);
}

bool BombPlayer::CanMove()
{
	// player can move if he doesn't have to put a bomb
	return putBomb == false;
}

void BombPlayer::UpdatePutBomb()
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

void BombPlayer::Update(float dt)
{
	BasePlayer::Update(dt);

	UpdatePutBomb();
}