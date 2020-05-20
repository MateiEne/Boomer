#include "SurpriseType.h"

SurpriseType SurpriseTypeUtils::GetRandomSurpriseForPlayer()
{
	srand(time(NULL));

	SurpriseType surprise = SurpriseType::NONE;
	int surprisesCount = 3; /* there are only 4 surprises (not 6), because we don t want
							the player to get either none nor invincible surprise */

	int surpriseNumber = rand() % surprisesCount;


	/* 0 is for bombs supply
	1 is for blast radius
	2 is for speed */
	switch (surpriseNumber)
	{
	case 0:
		surprise = SurpriseType::BOMBS_SUPPLY;
		break;

	case 1:
		surprise = SurpriseType::BLAST_RADIUS;
		break;

	case 2:
		surprise = SurpriseType::SPEED;
		break;
	}

	return surprise;
}