#pragma once

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
};