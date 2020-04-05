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

	constexpr int BOX_COUNT = 5;

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

		namespace Stay
		{
			constexpr char TAG[] = "stay";
			constexpr float TIME_FRAME_CHANGE_COUNT = 0.5;

			constexpr MatPos FRAMES[] = { MatPos(0, 11), MatPos(0, 12) };
			constexpr int COUNT = 2;

			constexpr int DEFAULT_FRAME = 0;
		}

		namespace Move
		{
			constexpr char TAG[] = "move";
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

		namespace PutBomb
		{
			constexpr char TAG[] = "putBomb";
			constexpr float TIME_FRAME_CHANGE_COUNT = 0.08;

			namespace Down
			{
				constexpr int LINE = 2;
				constexpr int FRAMES[] = { 0, 1, 2, 3, 4, 5, 4, 3, 6, 0 };
				constexpr int COUNT = 10;

				constexpr int DEFAULT_FRAME = 0;
			}

			namespace Up
			{
				constexpr int LINE = 0;
				constexpr int FRAMES[] = { 0, 1, 2, 3, 4, 5, 4, 3, 6, 0 };
				constexpr int COUNT = 10;

				constexpr int DEFAULT_FRAME = 0;
			}

			namespace Right
			{
				constexpr int LINE = 3;
				constexpr int FRAMES[] = { 0, 1, 2, 3, 4, 5, 4, 6, 3, 0 };
				constexpr int COUNT = 10;

				constexpr int DEFAULT_FRAME = 0;
			}

			namespace Left
			{
				constexpr int LINE = 1;
				constexpr int FRAMES[] = { 0, 1, 2, 3, 4, 5, 4, 6, 3, 0 };
				constexpr int COUNT = 10;

				constexpr int DEFAULT_FRAME = 0;
			}
		}
	}
}

namespace DeadWalkerConst
{
	constexpr float STAY_PROBABILITY = 0.1;
	constexpr float STAY_TIME = 4;

	namespace DirectionsProbability
	{
		constexpr float SAME = 0.2;
		constexpr float OPPOSITE = 0.05;
		constexpr float SIDE = 0.75;
	}
}