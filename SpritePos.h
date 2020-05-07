#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class SpritePos
{
public:
	SpritePos(sf::Vector2f position, sf::IntRect frame)
	{
		this->position = position;
		this->frame = frame;
	}

	sf::Vector2f position;
	sf::IntRect frame;
};

