#include "BombPlayer.h"

using namespace PlayerConst;

BombPlayer::BombPlayer(World* world, BombsManager* bombsManager, const char* texture, const char* bombTexture, MatPos pos, string name) :
	BasePlayer(world, texture, pos, name),
	bombCreationAnimation{ SpriteSheet::PutBomb::Creation::TAG },
	putBombDownAnimation{ SpriteSheet::PutBomb::TAG }
	//putBombLeftAnimation{ SpriteSheet::PutBomb::TAG },
	//putBombRightAnimation{ SpriteSheet::PutBomb::TAG },
	//putBombUpAnimation{ SpriteSheet::PutBomb::TAG }
{
	if (!this->bombTexture.loadFromFile(bombTexture))
	{
		cout << "error loading bomb spriteSheetTexture";
		exit(-1);
	}

	InitBombSprite();
	InitBombAnimations();

	this->bombsManager = bombsManager;

	putBomb = false;
}

void BombPlayer::InitBombSprite()
{
	bombSprite.setTexture(bombTexture);

	bombScale = sf::Vector2f(
		WorldConst::CELL_WIDTH / BombDefault::WIDTH * BombDefault::SCALE.x,
		WorldConst::CELL_HEIGHT / BombDefault::HEIGHT * BombDefault::SCALE.y
	);

	bombSprite.setScale(bombScale);

	bombSprite.setOrigin(
		BombDefault::WIDTH / 2.0f,
		BombDefault::HEIGHT / 2.0f
	);
}

void BombPlayer::InitBombAnimations()
{
	InitAnimation(
		putBombDownAnimation,
		SpriteSheet::PutBomb::Down::COUNT,
		SpriteSheet::PutBomb::Down::LINE,
		SpriteSheet::PutBomb::Down::FRAMES
	);
	/*InitAnimation(
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
	);*/

	InitBombCreationAnimation();
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

void BombPlayer::InitBombCreationAnimation()
{
	using namespace SpriteSheet::PutBomb;
	using namespace SpriteSheet::PutBomb::Creation;

	float stepsCount = FRAME_END_BOMB_CREATION - FRAME_BEGIN_BOMB_CREATION + 1;
	float step = (FINAL_SCALE - INITIAL_SCALE) / stepsCount;

	for (int i = 0; i < stepsCount; i++)
	{
		bombCreationAnimation.AddFrame(step * i);
	}


	/* 	If the bomb creation animation finishes before the put bomb animation,
	the bomb will disappear and then it will reappear when the bombsManager starts the fire bomb animation.

	To avoid this behaviour, we add frames to bomb creation animation to match the number of frames that
	put bomb animation has. These last frames have the FINAL_SCALE as values */
	for (int i = stepsCount; i < Down::COUNT; i++)
	{
		bombCreationAnimation.AddFrame(FINAL_SCALE);
	}
}

bool BombPlayer::CanPutBomb()
{
	return world->CanPutBomb(position) && bombsManager->CanPutBomb(name, BOMB_COUNT);
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

void BombPlayer::UpdatePutBomb(float dt)
{
	if (putBomb && ReachedDesirePostion())
	{
		if (!animation->Is(SpriteSheet::PutBomb::TAG))
		{
			ChangeAnimation(putBombDownAnimation, SpriteSheet::PutBomb::TIME_FRAME_CHANGE_COUNT, false);
			/*switch (direction)
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
			}*/
		}
		else
		{
			// check if the bomb creation animation should start
			if (animation->GetCurrentFrameIndex() == SpriteSheet::PutBomb::FRAME_BEGIN_BOMB_CREATION &&
				!bombCreationAnimation.IsPlaying())
			{
				bombCreationAnimation.Start(SpriteSheet::PutBomb::Creation::TIME_FRAME_CHANGE_COUNT, false);
				bombPosition = position;
			}

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

	UpdatePutBomb(dt);

	bombCreationAnimation.Update(dt);
}

void BombPlayer::Draw(sf::RenderWindow& window)
{
	BasePlayer::Draw(window);

	if (bombCreationAnimation.IsPlaying())
	{
		bombSprite.setScale(bombScale * bombCreationAnimation.GetCurrentFrame());
		bombSprite.setPosition(bombPosition + sf::Vector2f(WorldConst::CELL_WIDTH / 2, WorldConst::CELL_HEIGHT / 2));
		window.draw(bombSprite);
	}
}