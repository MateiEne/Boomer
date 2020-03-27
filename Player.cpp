#include "Player.h"

Player::Player(const char* texture) 
{
	if (!spriteSheetTexture.loadFromFile(texture))
	{
		cout << "error loading player spriteSheetTexture";
		exit(-1);
	}

	sprite.setTexture(spriteSheetTexture);
}

Player::~Player()
{
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}