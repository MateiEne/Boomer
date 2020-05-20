#pragma once
#include <iostream>
#include <time.h>
#include <list>
#include <stdlib.h>

using namespace std;

enum class SurpriseType
{
	NONE = '.',
	RANDOM = 'R',
	BOMBS_SUPPLY = 'B',
	BLAST_RADIUS = 'E',
	SPEED = 'S',
	INVINCIBLE = 'I'
};

inline ostream& operator << (ostream& os, const SurpriseType& surprise)
{
	os << surprise;

	return os;
}

namespace SurpriseTypeUtils
{
	SurpriseType GetRandomSurpriseForPlayer();
}