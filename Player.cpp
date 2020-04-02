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

	InitAnimation(rightAnimation, SpriteSheet::Move::Right::COUNT, SpriteSheet::Move::Right::LINE);
	InitAnimation(upAnimation, SpriteSheet::Move::Up::COUNT, SpriteSheet::Move::Up::LINE);
	InitAnimation(downAnimation, SpriteSheet::Move::Down::COUNT, SpriteSheet::Move::Down::LINE);
	InitAnimation(leftAnimation, SpriteSheet::Move::Left::COUNT, SpriteSheet::Move::Left::LINE);

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

	animation = &downAnimation;
	move = false;
	direction = Direction::DOWN;
}

Player::~Player()
{
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

void Player::InitAnimation(Animation& animation, int frames, int l)
{
	for (int i = 0; i < frames; i++)
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
	// don t change the position if the player isn t in the desire position
	if (position != desirePosition)
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
	// don t change the position if the player isn t in the desire position
	if (position != desirePosition)
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
	// don t change the position if the player isn t in the desire position
	if (position != desirePosition)
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
	// don t change the position if the player isn t in the desire position
	if (position != desirePosition)
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

bool Player::WillCollide(sf::Vector2f desirePosition)
{
	return !world->IsCellEmpty(desirePosition);
}

void Player::ChangeAnimation(Animation& animation, bool loop)
{
	this->animation = &animation;
	this->animation->Start(SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT, loop);
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
	else
	{
		animation->Stop();
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setTextureRect(animation->GetCurrentFrame());
	window.draw(sprite);
}