#include "Player.h"

using namespace PlayerConst;

Player::Player(World* world, BombsManager* bombsManager, const char* texture, MatPos pos, string name) :
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

Player::~Player()
{
}

void Player::InitAnimations()
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

void Player::InitAnimation(Animation<sf::IntRect>& animation, int count, int l)
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

void Player::InitAnimation(Animation<sf::IntRect>& animation, const int count, const int l, const int frames[])
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

void Player::MoveUp()
{
	if (!CanMove())
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
			ChangeAnimation(upAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
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
	ChangeAnimation(upAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
	move = true;
}

void Player::MoveDown()
{
	if (!CanMove())
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
			ChangeAnimation(downAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
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
	ChangeAnimation(downAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
	move = true;
}

void Player::MoveLeft()
{
	if (!CanMove())
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
			ChangeAnimation(leftAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
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
	ChangeAnimation(leftAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
	move = true;
}

void Player::MoveRight()
{
	if (!CanMove())
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
			ChangeAnimation(rightAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
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
	ChangeAnimation(rightAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
	move = true;
}

bool Player::CanMove()
{
	// player can move if he doesn't have to put a bomb
	return putBomb == false;
}

bool Player::CanPutBomb()
{
	return world->IsCellEmpty(position);
}

void Player::PutBomb()
{
	if (!CanPutBomb())	
	{
		return;
	}

	putBomb = true;
}

bool Player::WillCollide(sf::Vector2f desirePosition)
{
	return world->IsCellBox(desirePosition) || world->IsCellWall(desirePosition);
}

void Player::ChangeAnimation(Animation<sf::IntRect>& animation, float changeFrameTime, bool loop)
{
	if (this->animation == &animation && this->animation->IsPlaying())
	{
		return;
	}

	prevAnimation = this->animation;

	this->animation = &animation;
	this->animation->Start(changeFrameTime, loop);
}

bool Player::ReachedDesirePostion()
{
	return position == desirePosition;
}

MatPos Player::GetMatPlayerPosition()
{
	MatPos playerPos;

	playerPos.l = position.y / WorldConst::CELL_HEIGHT;
	playerPos.c = position.x / WorldConst::CELL_WIDTH;

	return playerPos;
}

void Player::FireBomb()
{
	MatPos playerPos = GetMatPlayerPosition();

	bombsManager->PutBomb(playerPos, name);
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
	else if (animation->Is(SpriteSheet::Move::TAG))
	{
		animation->Stop();
	}

	if (putBomb && position == desirePosition)
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

void Player::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setTextureRect(animation->GetCurrentFrame());
	window.draw(sprite);
}