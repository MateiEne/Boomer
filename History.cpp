#include "History.h"

History::History(int size, float timeBetween)
{
	this->size = size;
	this->timeBetween = timeBetween;

	timeCounter = 0;
}

bool History::ShouldAddRecord()
{
	return timeCounter >= timeBetween;
}

void History::AddRecord(SpritePos spritePos)
{
	if (!ShouldAddRecord())
	{
		return;
	}

	timeCounter = 0;

	if (records.size() < size)
	{
		records.push_back(spritePos);
		return;
	}

	records.push_back(spritePos);
	records.pop_front();
}

deque<SpritePos> History::GetRecords()
{
	return records;
}

void History::Update(float dt)
{
	timeCounter += dt;
}