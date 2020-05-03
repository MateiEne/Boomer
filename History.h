#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>

#include "SpritePos.h"

using namespace std;

class History
{
public:
	History(int size, float timeBetween);

	void Update(float dt);

	bool ShouldAddRecord();
	void AddRecord(SpritePos spritePos);
	deque<SpritePos> GetRecords();

private:
	int size;

	float timeCounter;
	float timeBetween;

	deque<SpritePos> records;
};

