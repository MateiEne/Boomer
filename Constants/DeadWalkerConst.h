#pragma once
#include <SFML/Graphics.hpp>

namespace DeadWalkerConst
{
	constexpr float STAY_PROBABILITY = 0.1;
	constexpr float STAY_TIME = 4;

	const sf::Color COLOR = sf::Color(255, 255, 255, 200);

	namespace Shadow
	{
		constexpr int COUNT = 5;
		constexpr float RECORD_TIME = 0.2;

		constexpr int BASE_ALPHA = 100;
		constexpr int STEP_ALPHA = 10;
	}

	namespace DirectionsProbability
	{
		constexpr float SAME = 0.2;
		constexpr float OPPOSITE = 0.05;
		constexpr float SIDE = 0.75;
	}
}