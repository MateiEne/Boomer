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
	bombSprite.setTextureRect(
		sf::IntRect(
			BombConst::SpriteSheet::DEFAULT_FRAME.c * BombConst::SpriteSheet::FRAME_WIDTH,
			BombConst::SpriteSheet::DEFAULT_FRAME.l * BombConst::SpriteSheet::FRAME_HEIGHT,
			BombConst::SpriteSheet::FRAME_WIDTH,
			BombConst::SpriteSheet::FRAME_HEIGHT
		)
	);

	bombScale = sf::Vector2f(
		WorldConst::CELL_WIDTH / BombConst::SpriteSheet::FRAME_WIDTH,
		WorldConst::CELL_HEIGHT / BombConst::SpriteSheet::FRAME_HEIGHT
	);

	bombSprite.setScale(bombScale);

	bombSprite.setOrigin(
		BombConst::SpriteSheet::FRAME_WIDTH / 2.0f,
		BombConst::SpriteSheet::FRAME_HEIGHT / 2.0f
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
	using namespace SpriteSheet::PutBomb::Creation;

	float step = (FINAL_SCALE - INITIAL_SCALE) / (STEPS_COUNT);

	for (int i = 0; i < STEPS_COUNT; i++)
	{
		bombCreationAnimation.AddFrame(step * i);
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

			bombCreationAnimation.Start(SpriteSheet::PutBomb::Creation::TIME_FRAME_CHANGE_COUNT, false);
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
			bombCreationAnimation.Update(dt);

			cout << bombCreationAnimation.GetCurrentFrame() << endl;

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
}

void BombPlayer::Draw(sf::RenderWindow& window)
{
	BasePlayer::Draw(window);

	if (putBomb)
	{
		bombSprite.setScale(bombScale * bombCreationAnimation.GetCurrentFrame());
		bombSprite.setPosition(position + sf::Vector2f(WorldConst::CELL_WIDTH / 2, WorldConst::CELL_HEIGHT / 2));
		window.draw(bombSprite);
	}
}