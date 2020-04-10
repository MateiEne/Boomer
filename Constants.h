#pragma once
#include <SFML/Graphics.hpp>
#include "MatPos.h"

namespace WorldConst
{
	constexpr int NL = 7;
	constexpr int NC = 7;

	constexpr float CELL_WIDTH = 100;
	constexpr float CELL_HEIGHT = 100;

	constexpr char WALL = 'x';
	constexpr char BOX = 'o';
	constexpr char FLOOR = '.';

	constexpr int BOX_COUNT = 0;
	constexpr int REMOVABLE_WALLS = 25;

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


namespace BombConst
{
	namespace SpriteSheet
	{
		constexpr float FRAME_WIDTH = 160;
		constexpr float FRAME_HEIGHT = 160;

		constexpr MatPos DEFAULT_FRAME(2, 0);

		namespace Fire
		{
			constexpr char TAG[] = "bombFire";
			constexpr float TIME_FRAME_CHANGE_COUNT = 0.08;
			
			constexpr int FRAME_START_EXPLOSION = 10;

			constexpr MatPos FRAMES[] = 
			{
				MatPos(2, 0), MatPos(2, 1), MatPos(2, 2), MatPos(2, 3), MatPos(2, 4),
				MatPos(3, 0), MatPos(3, 1), MatPos(3, 2),
				MatPos(0, 0), MatPos(0, 1), MatPos(0, 2), MatPos(0, 3), MatPos(0, 4),
				MatPos(1, 0), MatPos(1, 1), MatPos(1, 2), MatPos(1, 3), MatPos(1, 4),
			};
			constexpr int COUNT = 18;
		}

		namespace Drop
		{
			constexpr char TAG[] = "bombDrop";

			constexpr MatPos FRAMES[] = { MatPos(4, 0), MatPos(4, 1), MatPos(4, 2), MatPos(4, 3) };
			constexpr int COUNT = 4;
		}
	}
}


namespace ExplosionConst
{
	constexpr float TOTAL_TIME = (BombConst::SpriteSheet::Fire::COUNT - BombConst::SpriteSheet::Fire::FRAME_START_EXPLOSION) * BombConst::SpriteSheet::Fire::TIME_FRAME_CHANGE_COUNT;

	namespace LengthAnimation
	{
		constexpr char TAG[] = "explosionLength";

		constexpr float INCREASE_TIME_PERCENT = 0.2;
		constexpr float PEAK_TIME_PERCENT = 0.35;
		constexpr float DECREASE_TIME_PERCENT = 0.15;
	}

	namespace SpriteSheet
	{
		constexpr float FRAME_WIDTH = 32;
		constexpr float FRAME_HEIGHT = 32;

		constexpr char TAG[] = "explosion";

		constexpr MatPos CENTER[] =		{ MatPos(1, 0), MatPos(0, 0), MatPos(1, 0), MatPos(2, 0), MatPos(3, 0) };
		constexpr MatPos SIDE_Y[] =		{ MatPos(1, 1), MatPos(0, 1), MatPos(1, 1), MatPos(2, 1), MatPos(3, 1) };
		constexpr MatPos SIDE_X[] =		{ MatPos(1, 2), MatPos(0, 2), MatPos(1, 2), MatPos(2, 2), MatPos(3, 2) };
		constexpr MatPos PEAK_DOWN[] =	{ MatPos(1, 3), MatPos(0, 3), MatPos(1, 3), MatPos(2, 3), MatPos(3, 3) };
		constexpr MatPos PEAK_UP[] =	{ MatPos(1, 4), MatPos(0, 4), MatPos(1, 4), MatPos(2, 4), MatPos(3, 4) };
		constexpr MatPos PEAK_RIGHT[] = { MatPos(1, 5), MatPos(0, 5), MatPos(1, 5), MatPos(2, 5), MatPos(3, 5) };
		constexpr MatPos PEAK_LEFT[] =	{ MatPos(1, 6), MatPos(0, 6), MatPos(1, 6), MatPos(2, 6), MatPos(3, 6) };
		constexpr int COUNT = 5;

		constexpr float TIME_FRAME_CHANGE_COUNT = TOTAL_TIME * (LengthAnimation::INCREASE_TIME_PERCENT + LengthAnimation::PEAK_TIME_PERCENT + LengthAnimation::DECREASE_TIME_PERCENT / 2) / COUNT;
	}
}