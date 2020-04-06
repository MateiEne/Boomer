#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "Constants.h"
#include "Direction.h"


using namespace std;

class MazeGenerator
{
public:
	MazeGenerator();
	~MazeGenerator();

	void Generate(char map[][50], int nl, int nc);
	void GenerateTwin(char map[][50], int nl, int nc);

private:
	void PrintMap(char map[][50], int nl, int nc);
	void InitializeMap(char map[][50], int nl, int nc);
	void GetStartingPosition(char map[][50], int nl, int nc, int& l, int& c);
	void GenerateMaze(char map[][50], int nl, int nc, int l, int c);
	void RemoveDeadEnds(char mp[][50], int nl, int nc);
	bool IsDeadEnd(char map[][50], int nl, int nc, int l, int c);
	void RemoveDeadEnd(char map[][50], int nl, int nc, int l, int c);
	void MergeMatrix(char dest[][50], char first[][50], char second[][50], int nl, int nc);
	void RemoveMiddleWalls(char map[][50], int nl, int nc);
};

