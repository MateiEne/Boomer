#pragma once

class MatPos
{
public:
	int l, c;

	MatPos()
	{
		l = c = 0;
	}

	MatPos(int l, int c)
	{
		this->l = l;
		this->c = c;
	}
};