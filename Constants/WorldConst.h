#pragma once
#include <SFML/Graphics.hpp>
#include "../MatPos.h"

namespace WorldConst
{
	constexpr int NL = 15;
	constexpr int NC = 30;
	//constexpr int NL = 9;
	//constexpr int NC = 14;

	constexpr float CELL_WIDTH = 64;
	constexpr float CELL_HEIGHT = 64;

	constexpr float BASE_GROUND = 10;

	constexpr char WALL = 'x';
	constexpr char BOX = 'o';
	constexpr char FLOOR = '.';
	constexpr char BOMB = '*';
	constexpr char EXPLOSION = '#';
	constexpr char EXPLOSION_DANGER = '+';

	constexpr int BOXES_COUNT = 100;
	constexpr int REMOVABLE_WALLS = 0;

	namespace SpriteSheet
	{
		constexpr float FRAME_WIDTH = 196;
		constexpr float FRAME_HEIGHT = 196;

		constexpr MatPos WALL(1, 0);
		constexpr MatPos BOX(4, 2);
		constexpr MatPos FLOOR(2, 2);
	}

	const sf::Color BG_COLOR(186, 155, 112);
	const sf::Color BG_COLOR_TRANSPARENT(BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, 0);
}