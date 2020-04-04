#include "MazeGenerator.h"

MazeGenerator::MazeGenerator()
{
	srand(time(NULL));
}

MazeGenerator::~MazeGenerator()
{
}

void MazeGenerator::PrintMap(char map[][50], int nl, int nc)
{
	for (int i = 0; i < nl; i++)
	{
		for (int j = 0; j < nc; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void MazeGenerator::Generate(char map[][50], int nl, int nc)
{
	InitializeMap(map, nl, nc);

	int startL, startC;
	GetStartingPosition(map, nl, nc, startL, startC);

	GenerateMaze(map, nl, nc, startL, startC);

	RemoveDeadEnds(map, nl, nc);
}

void MazeGenerator::InitializeMap(char map[][50], int nl, int nc)
{
	// walls everywhere
	for (int i = 0; i < nl; i++)
	{
		for (int j = 0; j < nc; j++)
		{
			map[i][j] = WorldConst::WALL;
		}
	}
}

void MazeGenerator::GetStartingPosition(char map[][50], int nl, int nc, int& l, int& c)
{
	do
	{
		l = rand() % nl - 1;
		c = rand() % nc - 1;

	} while (!IsGoodCell(l, c));
}

bool MazeGenerator::IsGoodCell(int l, int c)
{
	// l, c > 1 and l, c odd numbers
	return l > 1 && c > 1 && l % 2 == 1 && c % 2 == 1;
}

void MazeGenerator::GenerateMaze(char map[][50], int nl, int nc, int l, int c)
{
	vector<Direction> directions = ShuffleDirections();

	for (Direction direction : directions)
	{
		switch (direction)
		{
		case Direction::UP:
			if (l - 2 <= 0)
			{
				continue;
			}

			if (map[l - 2][c] == WorldConst::WALL)
			{
				map[l - 1][c] = map[l - 2][c] = WorldConst::FLOOR;
				GenerateMaze(map, nl, nc, l - 2, c);
			}
			break;

		case Direction::RIGHT:
			if (c + 2 >= nc - 1)
			{
				continue;
			}

			if (map[l][c + 2] == WorldConst::WALL)
			{
				map[l][c + 1] = map[l][c + 2] = WorldConst::FLOOR;
				GenerateMaze(map, nl, nc, l, c + 2);
			}
			break;

		case Direction::DOWN:
			if (l + 2 >= nl - 1)
			{
				continue;
			}

			if (map[l + 2][c] == WorldConst::WALL)
			{
				map[l + 1][c] = map[l + 2][c] = WorldConst::FLOOR;
				GenerateMaze(map, nl, nc, l + 2, c);
			}
			break;

		case Direction::LEFT:
			if (c - 1 <= 0)
			{
				continue;
			}

			if (map[l][c - 2] == WorldConst::WALL)
			{
				map[l][c - 1] = map[l][c - 2] = WorldConst::FLOOR;
				GenerateMaze(map, nl, nc, l, c - 2);
			}
			break;
		}
	}
}

void MazeGenerator::RemoveDeadEnds(char map[][50], int nl, int nc)
{
	for (int i = 1; i < nl - 1; i++)
	{
		for (int j = 1; j < nc - 1; j++)
		{
			if (map[i][j] == WorldConst::FLOOR && IsDeadEnd(map, nl, nc, i, j))
			{
				RemoveDeadEnd(map, nl, nc, i, j);
			}
		}
	}
}

bool MazeGenerator::IsDeadEnd(char map[][50], int nl, int nc, int l, int c)
{
	int surroundingWalls = 0;

	if (l + 1 < nl && map[l + 1][c] == WorldConst::WALL)
		surroundingWalls++;

	if (l - 1 >= 0 && map[l - 1][c] == WorldConst::WALL)
		surroundingWalls++;

	if (c + 1 < nc && map[l][c + 1] == WorldConst::WALL)
		surroundingWalls++;

	if (c - 1 >= 0 && map[l][c - 1] == WorldConst::WALL)
		surroundingWalls++;

	return surroundingWalls == 3;
}

void MazeGenerator::RemoveDeadEnd(char map[][50], int nl, int nc, int l, int c)
{
	if (l - 1 > 0 && map[l - 1][c] == WorldConst::WALL)
	{
		map[l - 1][c] = WorldConst::FLOOR;
	}
	else if (c - 1 > 0 && map[l][c - 1] == WorldConst::WALL)
	{
		map[l][c - 1] = WorldConst::FLOOR;
	}
	else if (l + 1 < nl - 1 && map[l + 1][c] == WorldConst::WALL)
	{
		map[l + 1][c] = WorldConst::FLOOR;
	}
	else if (c + 1 < nc - 1 && map[l][c + 1] == WorldConst::WALL)
	{
		map[l][c + 1] = WorldConst::FLOOR;
	}
}