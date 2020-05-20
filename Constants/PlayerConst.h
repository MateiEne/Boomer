#pragma once
#include "../MatPos.h"
#include "BombConst.h"

namespace PlayerConst
{
	constexpr float SPEED = 100;
	constexpr int SPEED_STEP_INCREASE = 20;
	constexpr int MAX_SPEED = 180;

	constexpr int BOMBS_COUNT = 2;
	constexpr int BOMBS_COUNT_STEP_INCREASE = 1;
	constexpr int BOMBS_MAX_COUNT = 4;

	constexpr int BLAST_LENGTH = 3;
	constexpr int BLAST_LENGTH_STEP_INCREASE = 1;
	constexpr int BLAST_MAX_LENGTH = 7;

	constexpr int LIFES_COUNT = 300;
	constexpr float INVINCIBLE_TIME_AFTER_HIT = 3;
	const sf::Color INVINCIBLE_COLOR = sf::Color(255, 255, 255, 80);

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

		namespace Dead
		{
			constexpr char TAG[] = "dead";
			constexpr float TIME_FRAME_CHANGE_COUNT = 0.2;

			constexpr int LINE = 20;
			constexpr int COUNT = 6;

			constexpr int DEFAULT_FRAME = 0;
		}

		namespace LifeLost
		{
			constexpr char TAG[] = "LifeLost";
			constexpr float TIME_FRAME_CHANGE_COUNT = 0.07;

			constexpr int LINE = 20;
			constexpr int COUNT = 24;

			constexpr int FRAMES[] = { 0, 0, 0, 0, 0, 0, 1, 2, 4, 5, 5, 5, 5, 5, 5, 5, 5, 4, 3, 3, 3, 2, 1, 0 };

			constexpr int DEFAULT_FRAME = 0;
		}

		namespace Shoot
		{
			constexpr char TAG[] = "shoot";
			constexpr float TIME_FRAME_CHANGE_COUNT = 0.1f;

			namespace  Down
			{
				constexpr int LINE = 18;
				constexpr int COUNT = 12;

				constexpr int DEFAULT_FRAME = 0;
			}

			namespace Up
			{
				constexpr int LINE = 16;
				constexpr int COUNT = 12;

				constexpr int DEFAULT_FRAME = 0;
			}

			namespace Left
			{
				constexpr int LINE = 17;
				constexpr int COUNT = 12;

				constexpr int DEFAULT_FRAME = 0;
			}

			namespace Right
			{
				constexpr int LINE = 19;
				constexpr int COUNT = 12;

				constexpr int DEFAULT_FRAME = 0;
			}
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