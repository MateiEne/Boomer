#pragma once
#include "../MatPos.h"

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
			constexpr float TIME_FRAME_CHANGE_COUNT = 0.2;

			constexpr int FRAME_BEGIN_EXPLOSION = 10;

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
	constexpr float TOTAL_TIME = (BombConst::SpriteSheet::Fire::COUNT - BombConst::SpriteSheet::Fire::FRAME_BEGIN_EXPLOSION) * BombConst::SpriteSheet::Fire::TIME_FRAME_CHANGE_COUNT;

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

		constexpr MatPos CENTER[] = { MatPos(1, 0), MatPos(0, 0), MatPos(1, 0), MatPos(2, 0), MatPos(3, 0) };
		constexpr MatPos SIDE_Y[] = { MatPos(1, 1), MatPos(0, 1), MatPos(1, 1), MatPos(2, 1), MatPos(3, 1) };
		constexpr MatPos SIDE_X[] = { MatPos(1, 2), MatPos(0, 2), MatPos(1, 2), MatPos(2, 2), MatPos(3, 2) };
		constexpr MatPos PEAK_DOWN[] = { MatPos(1, 3), MatPos(0, 3), MatPos(1, 3), MatPos(2, 3), MatPos(3, 3) };
		constexpr MatPos PEAK_UP[] = { MatPos(1, 4), MatPos(0, 4), MatPos(1, 4), MatPos(2, 4), MatPos(3, 4) };
		constexpr MatPos PEAK_RIGHT[] = { MatPos(1, 5), MatPos(0, 5), MatPos(1, 5), MatPos(2, 5), MatPos(3, 5) };
		constexpr MatPos PEAK_LEFT[] = { MatPos(1, 6), MatPos(0, 6), MatPos(1, 6), MatPos(2, 6), MatPos(3, 6) };
		constexpr int COUNT = 5;

		constexpr float TIME_FRAME_CHANGE_COUNT = TOTAL_TIME * (LengthAnimation::INCREASE_TIME_PERCENT + LengthAnimation::PEAK_TIME_PERCENT + LengthAnimation::DECREASE_TIME_PERCENT / 2) / COUNT;
	}
}