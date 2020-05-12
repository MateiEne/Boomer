#include "BombPlayer.h"

using namespace PlayerConst;

BombPlayer::BombPlayer(World* world, BombsManager* bombsManager, const char* texture, const char* bombTexture, MatPos pos, string name) :
	BasePlayer(world, texture, pos, name),
	bombCreationScaleAnimation{ SpriteSheet::PutBomb::Creation::TAG },
	bombCreationPositionAnimation{ SpriteSheet::PutBomb::Creation::TAG },
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

	InitBombCreationScaleAnimation();
}

void BombPlayer::InitBombCreationScaleAnimation()
{
	using namespace SpriteSheet::PutBomb;
	using namespace SpriteSheet::PutBomb::Creation;

	sf::Vector2f initialScale(
		WorldConst::CELL_WIDTH / BombDefault::WIDTH * BombDefault::SCALE.x,
		WorldConst::CELL_HEIGHT / BombDefault::HEIGHT * BombDefault::SCALE.y
	);

	float stepsCount = FRAME_END_BOMB_CREATION - FRAME_BEGIN_BOMB_CREATION + 1;
	sf::Vector2f step(
		(FINAL_SCALE.x - INITIAL_SCALE.x) / stepsCount,
		(FINAL_SCALE.y - INITIAL_SCALE.y) / stepsCount
	);

	for (int i = 0; i < stepsCount; i++)
	{
		bombCreationScaleAnimation.AddFrame(
			sf::Vector2f(
				step.x * i * initialScale.x, 
				step.y * i * initialScale.y
			)
		);
	}

	/* 	If the bomb creation animation finishes before the put bomb animation,
	the bomb will disappear and then it will reappear when the bombsManager starts the fire bomb animation.

	To avoid this behaviour, we add the FINAL_SCALE frame to bomb creation animation and it will play this frame
	until the put bomb animation will finish. */
	bombCreationScaleAnimation.AddFrame(
		sf::Vector2f(
			FINAL_SCALE.x * initialScale.x,
			FINAL_SCALE.y * initialScale.y
		)
	);
}

void BombPlayer::InitBombCreationPositionAnimation(sf::Vector2f initialPosition)
{
	using namespace SpriteSheet::PutBomb;
	using namespace SpriteSheet::PutBomb::Creation;

	float stepsCount = FRAME_END_BOMB_CREATION - FRAME_BEGIN_BOMB_CREATION + 1;
	sf::Vector2f step(
		(FINAL_OFFSET.x - INITIAL_OFFSET.x) / stepsCount,
		(FINAL_OFFSET.y - INITIAL_OFFSET.y) / stepsCount
	);

	/* 	If the bomb creation animation finishes before the put bomb animation,
	the bomb will disappear and then it will reappear when the bombsManager starts the fire bomb animation.

	To avoid this behaviour, we add the FINAL_SCALE frame to bomb creation animation and it will play this frame
	until the put bomb animation will finish. */
	for (int i = 0; i < stepsCount; i++)
	{
		bombCreationPositionAnimation.AddFrame(initialPosition + sf::Vector2f(step.x * i, step.y * i));
	}

	bombCreationPositionAnimation.AddFrame(initialPosition + FINAL_OFFSET);
}

void BombPlayer::ResetBombCreationAnimations(sf::Vector2f initialPosition)
{
	bombCreationScaleAnimation.Reset();
	bombCreationPositionAnimation.Clear();

	InitBombCreationPositionAnimation(position);
}

bool BombPlayer::CanPutBomb()
{
	if (IsKilled())
	{
		return false;
	}

	if (lifeLostAnimation.IsPlaying())
	{
		return false;
	}

	if (world->CanPutBomb(position) && bombsManager->CanPutBomb(name, BOMB_COUNT))
	{
		return true;
	}
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
	return BasePlayer::CanMove() && putBomb == false;
}

void BombPlayer::UpdatePutBomb(float dt)
{
	if (putBomb && IsInGoodMatPosition())
	{
		if (!animation->Is(SpriteSheet::PutBomb::TAG))
		{
			ChangeAnimation(putBombDownAnimation, SpriteSheet::PutBomb::TIME_FRAME_CHANGE_COUNT, false);

			ResetBombCreationAnimations(position);
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
				!bombCreationScaleAnimation.IsPlaying())
			{
				bombCreationScaleAnimation.Start(SpriteSheet::PutBomb::Creation::TIME_FRAME_CHANGE_COUNT, false);

				bombCreationPositionAnimation.Start(SpriteSheet::PutBomb::Creation::TIME_FRAME_CHANGE_COUNT, false);
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

	bombCreationScaleAnimation.Update(dt);
	bombCreationPositionAnimation.Update(dt);
}

void BombPlayer::Draw(DrawManager& drawManager)
{
	BasePlayer::Draw(drawManager);

	if (animation->Is(SpriteSheet::PutBomb::TAG))
	{
		bombSprite.setScale(bombCreationScaleAnimation.GetCurrentFrame());
		bombSprite.setPosition(
			bombCreationPositionAnimation.GetCurrentFrame() +
			sf::Vector2f(WorldConst::CELL_WIDTH / 2, WorldConst::CELL_HEIGHT / 2)
		);
		drawManager.Draw(bombSprite);
	}
}