#pragma once
#include "SFML/Graphics.hpp"
#include "../MatPos.h"

namespace ArrowConst
{
	constexpr int SPEED = 100;

	namespace SpriteSheet
	{
		constexpr float FRAME_WIDTH = 64;
		constexpr float FRAME_HEIGHT = 64;

		constexpr float TIME_FRAME_CHANGE_COUNT = 0.1f;

		namespace Down
		{
			constexpr MatPos FRAME(1, 0);
		}

		namespace Up
		{
			constexpr MatPos FRAME(1, 1);
		}

		namespace Right
		{
			constexpr MatPos FRAME(0, 0);
		}

		namespace Left
		{
			constexpr MatPos FRAME(0, 1);
		}
	}
}