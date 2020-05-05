#pragma once
#include <iostream>

using namespace std;

enum class SurpriseType
{
	NONE = '.',
	RANDOM = 'R',
	BOMBS_SUPPLY = 'B'
};

inline ostream& operator << (ostream& os, const SurpriseType& surprise)
{
	os << surprise;

	return os;
}
