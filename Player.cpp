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

	//InitAnimation(rightAnimation, PLAYER_MOVE_RIGHT_FRAMES, PLAYER_MOVE_RIGHT_L);
	//InitAnimation(upAnimation, PLAYER_MOVE_UP_FRAMES, PLAYER_MOVE_UP_L);
	//InitAnimation(downAnimation, PLAYER_MOVE_DOWN_FRAMES, PLAYER_MOVE_DOWN_L);
	InitAnimation(leftAnimation, PLAYER_MOVE_LEFT_FRAMES, PLAYER_MOVE_LEFT_L);
	
	//downAnimation.Start(PLAYER_CHANGE_ANIMATION);
	//upAnimation.Start(PLAYER_CHANGE_ANIMATION);
	//rightAnimation.Start(PLAYER_CHANGE_ANIMATION);
	leftAnimation.Start(PLAYER_CHANGE_ANIMATION);
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

void Player::Update(float dt)
{
	//downAnimation.Update(dt);
	//upAnimation.Update(dt);
	//rightAnimation.Update(dt);
	leftAnimation.Update(dt);
}

void Player::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	//sprite.setTextureRect(downAnimation.GetCurrentFrame());
	//sprite.setTextureRect(upAnimation.GetCurrentFrame());
	//sprite.setTextureRect(rightAnimation.GetCurrentFrame());
	sprite.setTextureRect(leftAnimation.GetCurrentFrame());
	window.draw(sprite);
}