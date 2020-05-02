#pragma once
#include "../MatPos.h"
#include "BombConst.h"

namespace PlayerConst
{
	constexpr float SPEED = 100;
	constexpr int BOMB_COUNT = 3;
	constexpr int BOMB_LENGTH = 3;

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
			constexpr float TIME_FRAME_CHANGE_COUNT = 0.05;

			constexpr int FRAME_BEGIN_BOMB_CREATION = 1;
			constexpr int FRAME_END_BOMB_CREATION = 5;

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

			namespace Creation
			{
				constexpr char TAG[] = "creationBomb";
				constexpr float TIME_FRAME_CHANGE_COUNT = PutBomb::TIME_FRAME_CHANGE_COUNT;

				const sf::Vector2f INITIAL_SCALE(0, 0);
				const sf::Vector2f FINAL_SCALE(1, 1);

				const sf::Vector2f INITIAL_OFFSET(1, 0);
				const sf::Vector2f FINAL_OFFSET = BombDefault::OFFSET;
			}
		}
	}
}