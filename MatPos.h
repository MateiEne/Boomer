#pragma once
#include <iostream>

using namespace std;

class MatPos
{
public:
	int l, c;

	constexpr MatPos() : l{ 0 }, c{ 0 }
	{
	}

	constexpr MatPos(int l, int c) : l{ l }, c{ c }
	{
	}

	MatPos operator + (MatPos const& matPos)
	{
		MatPos result;
		result.l = l + matPos.l;
		result.c = c + matPos.c;

		return result;
	}

	bool operator == (MatPos const& matPos) const
	{
		return l == matPos.l && c == matPos.c;
	}

	bool operator != (MatPos const& matPos) const
	{
		return l != matPos.l || c != matPos.c;
	}

	bool operator < (MatPos const& matPos) const
	{
		return l < matPos.l || (l == matPos.l && c < matPos.c);
	}

	friend ostream& operator << (ostream& os, const MatPos &matPos)
	{
		os << "(" << matPos.l << ", " << matPos.c << ")";
		
		return os;
	}
};