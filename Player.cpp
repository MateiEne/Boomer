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

	for (int i = 0; i < PLAYER_MOVE_DOWN_FRAMES; i++)
	{
		animation.AddFrame(
			sf::IntRect(
				i * PLAYER_WIDTH,
				PLAYER_MOVE_DOWN_L * PLAYER_HEIGHT,
				PLAYER_WIDTH,
				PLAYER_HEIGHT
				)
			);
	}
	animation.Start(PLAYER_CHANGE_ANIMATION);
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

void Player::Update(float dt)
{
	animation.Update(dt);
}

void Player::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setTextureRect(animation.GetCurrentFrame());
	window.draw(sprite);
}