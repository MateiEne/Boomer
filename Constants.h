#pragma once
#include <SFML/Graphics.hpp>
#include "MatPos.h"

namespace WorldConst 
{
	constexpr int NL = 13;
	constexpr int NC = 25;

	constexpr float CELL_WIDTH = 50;
	constexpr float CELL_HEIGHT = 50;

	constexpr char WALL = 'x';
	constexpr char BOX = 'o';
	constexpr char FLOOR = '.';

	constexpr int BOX_COUNT = 10;

	namespace SpriteSheet
	{
		constexpr float FRAME_WIDTH = 196;
		constexpr float FRAME_HEIGHT = 196;

		constexpr MatPos WALL(1, 0);
		constexpr MatPos BOX(4, 2);
		constexpr MatPos FLOOR(2, 2);
	}

	const sf::Color BG_COLOR(186, 155, 112);
}


namespace PlayerConst
{
	constexpr float SPEED = 100;

	namespace SpriteSheet
	{
		constexpr float FRAME_WIDTH = 64;
		constexpr float FRAME_HEIGHT = 64;

		constexpr MatPos DEFAULT_FRAME(10, 0);

		namespace Move
		{
			constexpr float TIME_FRAME_CHANGE_COUNT = 0.1f;

			namespace Down
			{
				constexpr int LINE = 10;
				constexpr int COUNT = 9;

				constexpr int DEFAULT_FRAME = 0;
			}

			namespace Up
			{
				constexpr int LINE = 8;
				constexpr int COUNT = 9;

				constexpr int DEFAULT_FRAME = 0;
			}

			namespace Right
			{
				constexpr int LINE = 11;
				constexpr int COUNT = 9;

				constexpr int DEFAULT_FRAME = 0;
			}

			namespace Left
			{
				constexpr int LINE = 9;
				constexpr int COUNT = 9;

				constexpr int DEFAULT_FRAME = 0;
			}
		}
	}
}