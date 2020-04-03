#include "Player.h"

using namespace PlayerConst;

Player::Player(World& world, const char* texture, MatPos pos)
{
	if (!spriteSheetTexture.loadFromFile(texture))
	{
		cout << "error loading player spriteSheetTexture";
		exit(-1);
	}

	InitSprite();

	this->world = &world;

	position.x = pos.c * WorldConst::CELL_WIDTH;
	position.y = pos.l * WorldConst::CELL_HEIGHT;

	desirePosition = position;

	Init();

	animation = &downAnimation;
	move = false;
	putBomb = false;
	direction = Direction::DOWN;
}

Player::~Player()
{
}

void Player::Init()
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

	InitTurnAnimation(
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
	);
}

void Player::InitSprite()
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

void Player::InitAnimation(Animation& animation, int count, int l)
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

void Player::InitAnimation(Animation& animation, const int count, const int l, const int frames[])
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

void Player::InitTurnAnimation(
	Animation& animation,
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

void Player::MoveUp()
{
	if (putBomb == true)
	{
		return;
	}

	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::DOWN)
		{
			desirePosition.y -= WorldConst::CELL_HEIGHT;
			if (WillCollide(desirePosition))
			{
				desirePosition.y += WorldConst::CELL_HEIGHT;
				return;
			}

			direction = Direction::UP;
			ChangeAnimation(upAnimation);
			move = true;
		}
		return;
	}

	desirePosition = position;
	desirePosition.y -= WorldConst::CELL_HEIGHT;
	if (WillCollide(desirePosition))
	{
		// collision => reset desirePosition => player won't move
		desirePosition = position;
		return;
	}
	
	direction = Direction::UP;
	ChangeAnimation(upAnimation);
	move = true;
}

void Player::MoveDown()
{
	if (putBomb == true)
	{
		return;
	}

	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::UP)
		{
			desirePosition.y += WorldConst::CELL_HEIGHT;
			if (WillCollide(desirePosition))
			{
				desirePosition.y -= WorldConst::CELL_HEIGHT;
				return;
			}
			direction = Direction::DOWN;
			ChangeAnimation(downAnimation);
			move = true;
		}
		return;
	}

	desirePosition = position;
	desirePosition.y += WorldConst::CELL_HEIGHT;
	if (WillCollide(desirePosition))
	{
		// collision => reset desirePosition => player won't move
		desirePosition = position;
		return;
	}
	
	direction = Direction::DOWN;
	ChangeAnimation(downAnimation);
	move = true;
}

void Player::MoveLeft()
{
	if (putBomb == true)
	{
		return;
	}

	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::RIGHT)
		{
			desirePosition.x -= WorldConst::CELL_WIDTH;
			if (WillCollide(desirePosition))
			{
				desirePosition.x += WorldConst::CELL_WIDTH;
				return;
			}
			direction = Direction::LEFT;
			ChangeAnimation(leftAnimation);
			move = true;
		}
		return;
	}

	desirePosition = position;
	desirePosition.x -= WorldConst::CELL_WIDTH;
	if (WillCollide(desirePosition))
	{
		// collision => reset desirePosition => player won't move
		desirePosition = position;
		return;
	}
	
	direction = Direction::LEFT;
	ChangeAnimation(leftAnimation);
	move = true;
}

void Player::MoveRight()
{
	if (putBomb == true)
	{
		return;
	}

	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::LEFT)
		{
			desirePosition.x += WorldConst::CELL_WIDTH;
			if (WillCollide(desirePosition))
			{
				desirePosition.x -= WorldConst::CELL_WIDTH;
				return;
			}
			direction = Direction::RIGHT;
			ChangeAnimation(rightAnimation);
			move = true;
		}
		return;
	}

	desirePosition = position;
	desirePosition.x += WorldConst::CELL_WIDTH;
	if (WillCollide(desirePosition))
	{
		// collision => reset desirePosition => player won't move
		desirePosition = position;
		return;
	}
	
	direction = Direction::RIGHT;
	ChangeAnimation(rightAnimation);
	move = true;
}

void Player::PutBomb()
{
	if (putBomb) 
	{
		return;
	}

	putBomb = true;
}

bool Player::WillCollide(sf::Vector2f desirePosition)
{
	return !world->IsCellEmpty(desirePosition);
}

void Player::ChangeAnimation(Animation& animation, bool loop)
{
	if (this->animation == &animation && this->animation->IsPlaying())
	{
		return;
	}

	this->animation = &animation;
	this->animation->Start(SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT, loop);
}

void Player::ChangeAnimationOfPutBomb(Animation& animation, bool loop)
{
	this->animation = &animation;
	this->animation->Start(SpriteSheet::PutBomb::TIME_FRAME_CHANGE_COUNT, loop);
}

bool Player::IsMoveAnimation()
{
	return animation == &rightAnimation ||
		animation == &leftAnimation ||
		animation == &upAnimation ||
		animation == &downAnimation;
}

bool Player::IsPutBombAnimation()
{
	return animation == &putBombDownAnimation ||
		animation == &putBombLeftAnimation ||
		animation == &putBombRightAnimation ||
		animation == &putBombUpAnimation;
}

bool Player::ReachedDesirePostion()
{
	return position == desirePosition;
}

void Player::Update(float dt)
{
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


	if (putBomb && ReachedDesirePostion() && !IsPutBombAnimation())
	{
		switch (direction)
		{
		case Direction::RIGHT:
			ChangeAnimationOfPutBomb(putBombRightAnimation, false);
			break;

		case Direction::LEFT:
			ChangeAnimationOfPutBomb(putBombLeftAnimation, false);
			break;

		case Direction::DOWN:
			ChangeAnimationOfPutBomb(putBombDownAnimation, false);
			break;

		case Direction::UP:
			ChangeAnimationOfPutBomb(putBombUpAnimation, false);
			break;
		}
	}
	else if (IsPutBombAnimation())
	{
		// putBomb aniumation is playing
		if (!animation->IsPlaying())
		{
			putBomb = false;
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setTextureRect(animation->GetCurrentFrame());
	window.draw(sprite);
}