#pragma once
#include <iostream>

using namespace std;

enum class SurpriseType
{
	NONE = '.',
	RANDOM = 'R',
	BOMBS_SUPPLY = 'B',
	BLAST_RADIUS = 'E'
};

inline ostream& operator << (ostream& os, const SurpriseType& surprise)
{
	os << surprise;

	return os;
}
