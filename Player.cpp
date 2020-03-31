#include "Player.h"

Player::Player(const char* texture, MatPos pos)
{
	if (!spriteSheetTexture.loadFromFile(texture))
	{
		cout << "error loading player spriteSheetTexture";
		exit(-1);
	}

	InitSprite();

	position.x = pos.c * CELL_WIDTH;
	position.y = pos.l * CELL_HEIGHT;

	desirePosition = position;

	InitAnimation(rightAnimation, PLAYER_MOVE_RIGHT_FRAMES, PLAYER_MOVE_RIGHT_L);
	InitAnimation(upAnimation, PLAYER_MOVE_UP_FRAMES, PLAYER_MOVE_UP_L);
	InitAnimation(downAnimation, PLAYER_MOVE_DOWN_FRAMES, PLAYER_MOVE_DOWN_L);
	InitAnimation(leftAnimation, PLAYER_MOVE_LEFT_FRAMES, PLAYER_MOVE_LEFT_L);

	InitTurnAnimation(
		turnLeftAnimation,
		PLAYER_DEFAULT_DOWN_POS_C,
		PLAYER_DEFAULT_DOWN_POS_L,
		PLAYER_DEFAULT_LEFT_POS_C,
		PLAYER_DEFAULT_LEFT_POS_L
	);
	InitTurnAnimation(
		turnRightAnimation,
		PLAYER_DEFAULT_DOWN_POS_C,
		PLAYER_DEFAULT_DOWN_POS_L,
		PLAYER_DEFAULT_RIGHT_POS_C,
		PLAYER_DEFAULT_RIGHT_POS_L
	);
	InitTurnAnimation(
		turnUpAnimation,
		PLAYER_DEFAULT_RIGHT_POS_C,
		PLAYER_DEFAULT_RIGHT_POS_L,
		PLAYER_DEFAULT_UP_POS_C,
		PLAYER_DEFAULT_UP_POS_L
	);
	InitTurnAnimation(
		turnDownAnimation,
		PLAYER_DEFAULT_RIGHT_POS_C,
		PLAYER_DEFAULT_RIGHT_POS_L,
		PLAYER_DEFAULT_DOWN_POS_C,
		PLAYER_DEFAULT_DOWN_POS_L
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
			PLAYER_DEFAULT_POS_C * PLAYER_WIDTH,
			PLAYER_DEFAULT_POS_L * PLAYER_HEIGHT,
			PLAYER_WIDTH,
			PLAYER_HEIGHT
			)
		);
	sprite.setScale(CELL_WIDTH / PLAYER_WIDTH, CELL_HEIGHT / PLAYER_HEIGHT);
}

void Player::InitAnimation(Animation& animation, int frames, int l)
{
	for (int i = 0; i < frames; i++)
	{
		animation.AddFrame(
			sf::IntRect(
				i * PLAYER_WIDTH,
				l * PLAYER_HEIGHT,
				PLAYER_WIDTH,
				PLAYER_HEIGHT
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
			defaultFirstPosC * PLAYER_WIDTH,
			defaultFirstPosL * PLAYER_HEIGHT,
			PLAYER_WIDTH,
			PLAYER_HEIGHT
		)
	);
	animation.AddFrame(
		sf::IntRect(
			defaultSecondPosC * PLAYER_WIDTH,
			defaultSecondPosL * PLAYER_HEIGHT,
			PLAYER_WIDTH,
			PLAYER_HEIGHT
		)
	);
}

void Player::MoveUp()
{
	move = true;
	
	// don t change the position if the player isn t in the desire position
	if (position != desirePosition)
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::DOWN)
		{
			desirePosition.y -= CELL_WIDTH;
			direction = Direction::UP;
			ChangeAnimation(upAnimation);
		}
		return;
	}

	direction = Direction::UP;
	desirePosition = GetDesirePosition(direction);
	ChangeAnimation(upAnimation);
}

void Player::MoveDown()
{
	move = true;

	// don t change the position if the player isn t in the desire position
	if (position != desirePosition)
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::UP)
		{
			desirePosition.y += CELL_WIDTH;
			direction = Direction::DOWN;
			ChangeAnimation(downAnimation);
		}
		return;
	}

	direction = Direction::DOWN;
	desirePosition = GetDesirePosition(direction);
	ChangeAnimation(downAnimation);
}

void Player::MoveLeft()
{
	move = true;

	// don t change the position if the player isn t in the desire position
	if (position != desirePosition)
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::RIGHT)
		{
			desirePosition.x -= CELL_WIDTH;
			direction = Direction::LEFT;
			ChangeAnimation(leftAnimation);
		}
		return;
	}

	direction = Direction::LEFT;
	desirePosition = GetDesirePosition(direction);
	ChangeAnimation(leftAnimation);
}

void Player::MoveRight()
{
	move = true;

	// don t change the position if the player isn t in the desire position
	if (position != desirePosition)
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::LEFT)
		{
			desirePosition.x += CELL_WIDTH;
			direction = Direction::RIGHT;
			ChangeAnimation(rightAnimation);
		}
		return;
	}

	direction = Direction::RIGHT;
	desirePosition = GetDesirePosition(direction);
	ChangeAnimation(rightAnimation);
}

void Player::ChangeAnimation(Animation& animation, bool loop)
{
	this->animation = &animation;
	this->animation->Start(PLAYER_CHANGE_ANIMATION, loop);
}

sf::Vector2f Player::GetDesirePosition(Direction dir)
{
	sf::Vector2f result = position;
	MatPos matPos;
	matPos.l = (position.y + CELL_HEIGHT / 2) / CELL_HEIGHT;
	matPos.c = (position.x + CELL_WIDTH / 2) / CELL_WIDTH;

	switch (dir)
	{
	case Direction::RIGHT:
		result.x = (matPos.c + 1) * CELL_WIDTH;
		break;

	case Direction::LEFT:
		result.x = (matPos.c - 1) * CELL_WIDTH;
		break;

	case Direction::DOWN:
		result.y = (matPos.l + 1) * CELL_HEIGHT;
		break;

	case Direction::UP:
		result.y = (matPos.l - 1) * CELL_HEIGHT;
		break;
	}

	return result;
}

void Player::Update(float dt)
{
	animation->Update(dt);

	if (move == true)
	{
		switch (direction)
		{
		case Direction::RIGHT:
			position.x += PLAYER_SPEED * dt;
			if (position.x >= desirePosition.x)
			{
				desirePosition.x = position.x;
				move = false;
			}
			break;
		case Direction::LEFT:
			position.x -= PLAYER_SPEED * dt;
			if (position.x <= desirePosition.x)
			{
				desirePosition.x = position.x;
				move = false;
			}
			break;
		case Direction::DOWN:
			position.y += PLAYER_SPEED * dt;
			if (position.y >= desirePosition.y)
			{
				desirePosition.y = position.y;
				move = false;
			}
			break;
		case Direction::UP:
			position.y -= PLAYER_SPEED * dt;
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