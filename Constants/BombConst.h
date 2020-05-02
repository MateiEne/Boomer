#pragma once
#include <SFML/Graphics.hpp>
#include "WorldConst.h"
#include "../MatPos.h"

namespace BombDefault
{
	constexpr float WIDTH = 64;
	constexpr float HEIGHT = 64;

	const sf::Vector2f SCALE(0.5, 0.5);
	const sf::Vector2f OFFSET(4, WorldConst::BASE_GROUND - 3);
}

namespace BombFire
{
	namespace SpriteSheet
	{
		constexpr float FRAME_WIDTH = 64;
		constexpr float FRAME_HEIGHT = 64;

		const sf::Vector2f SCALE = BombDefault::SCALE;
		const sf::Vector2f OFFSET = BombDefault::OFFSET;

		constexpr char TAG[] = "bombFire";
		constexpr float TIME_FRAME_CHANGE_COUNT = 0.06;

		constexpr MatPos FRAMES[] =
		{
			MatPos(0, 0), MatPos(0, 1), MatPos(0, 2), MatPos(0, 3), MatPos(0, 4), MatPos(0, 5), MatPos(0, 6), MatPos(0, 7), MatPos(0, 8), MatPos(0, 9),
			MatPos(1, 0), MatPos(1, 1), MatPos(1, 2), MatPos(1, 3), MatPos(1, 4), MatPos(1, 5), MatPos(1, 6), MatPos(1, 7), MatPos(1, 8), MatPos(1, 9),
			MatPos(2, 0), MatPos(2, 1), MatPos(2, 2), MatPos(2, 3), MatPos(2, 4), MatPos(2, 5), MatPos(2, 6), MatPos(2, 7), MatPos(2, 8), MatPos(2, 9),
			MatPos(3, 0), MatPos(3, 1), MatPos(3, 2), MatPos(3, 3), MatPos(3, 4), MatPos(3, 5), MatPos(3, 6), MatPos(3, 7)
		};

		constexpr int COUNT = 38;
	}
}

namespace BombExposion
{
	namespace SpriteSheet
	{
		constexpr float FRAME_WIDTH = 160;
		constexpr float FRAME_HEIGHT = 160;

		const sf::Vector2f SCALE(2, 2);
		const sf::Vector2f OFFSET = BombDefault::OFFSET;

		constexpr char TAG[] = "bombExplosion";
		constexpr float TIME_FRAME_CHANGE_COUNT = 0.1;

		constexpr MatPos FRAMES[] =
		{
			MatPos(0, 0), MatPos(0, 1), MatPos(0, 2), MatPos(0, 3),
			MatPos(1, 0), MatPos(1, 1), MatPos(1, 2), MatPos(1, 3)
		};

		constexpr int COUNT = 8;
	}
}

namespace ExplosionConst
{
	constexpr float TOTAL_TIME = BombExposion::SpriteSheet::COUNT * BombExposion::SpriteSheet::TIME_FRAME_CHANGE_COUNT;

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

		constexpr char TAG[] = "explosionBody";
		
		const sf::Vector2f SCALE_CENTER(0.5, 0.5);
		const sf::Vector2f SCALE_X(0.5, 1);
		const sf::Vector2f SCALE_Y(1, 0.5);

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