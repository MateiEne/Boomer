#pragma once
#include <SFML/Graphics.hpp>
#include "../MatPos.h"
#include "WorldConst.h"

namespace SurprisesConst
{
	constexpr int SURPRISE_COUNT = WorldConst::BOXES_COUNT;
	constexpr int TIME_TO_BOOST_ABILITIES = 9;

	namespace SurpriseSprite
	{
		constexpr float FRAME_WIDTH = 64;
		constexpr float FRAME_HEIGHT = 64;

		constexpr MatPos RANDOM(0, 0);
		constexpr MatPos BOMB_SUPPLY(0, 1);
		constexpr MatPos BLAST_RADIUS(0, 2);
	}
}