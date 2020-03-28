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

	animation = downAnimation;
	move = false;
	direction = DOWN;
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
	direction = UP;
	ChangeAnimation(upAnimation);
}

void Player::MoveDown()
{
	move = true;
	direction = DOWN;
	ChangeAnimation(downAnimation);
}

void Player::MoveLeft()
{
	move = true;
	direction = LEFT;
	ChangeAnimation(leftAnimation);
}

void Player::MoveRight()
{
	move = true;
	direction = RIGHT;
	ChangeAnimation(rightAnimation);
}

void Player::ChangeAnimation(Animation animation, bool loop)
{
	this->animation.Stop();
	this->animation = animation;
	this->animation.Start(PLAYER_CHANGE_ANIMATION, loop);
}

void Player::Update(float dt)
{
	animation.Update(dt);
	if (move == true)
	{
		switch (direction)
		{
		case RIGHT:
			position.x += PLAYER_SPEED * dt;
			break;
		case LEFT:
			position.x -= PLAYER_SPEED * dt;
			break;
		case DOWN:
			position.y += PLAYER_SPEED * dt;
			break;
		case UP:
			position.y -= PLAYER_SPEED * dt;
			break;

		default:
			break;
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setTextureRect(animation.GetCurrentFrame());
	window.draw(sprite);
}