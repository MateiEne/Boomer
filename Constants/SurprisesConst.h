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

		constexpr MatPos RANDOM(1, 0);
		constexpr MatPos BOMB_SUPPLY(0, 1);
		constexpr MatPos SPEED(1, 1);
		constexpr MatPos BLAST_RADIUS(0, 2);
		constexpr MatPos INVINCIBLE(1, 2);
	}

	namespace SurpriseProbabity
	{
		constexpr float RANDOM = 0.2;
		constexpr float BOMBS_SUPPLY = 0.3;
		constexpr float BLAST_RADIUS = 0.25;
		constexpr float SPEED = 0.2;
		constexpr float INVINCIBLE = 0.05;
	}
}