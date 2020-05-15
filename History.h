#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>

#include "SpritePos.h"

using namespace std;

template<class T>
class History
{
public:
	History(int size, float timeBetween);

	void Update(float dt);

	bool ShouldAddRecord();
	void AddRecord(T record);
	deque<T> GetRecords();

private:
	int size;

	float timeCounter;
	float timeBetween;

	deque<T> records;
};

template<class T>
History<T>::History(int size, float timeBetween)
{
	this->size = size;
	this->timeBetween = timeBetween;

	timeCounter = 0;
}

template<class T>
bool History<T>::ShouldAddRecord()
{
	return timeCounter >= timeBetween;
}

template<class T>
void History<T>::AddRecord(T record)
{
	if (!ShouldAddRecord())
	{
		return;
	}

	timeCounter = 0;

	if (records.size() < size)
	{
		records.push_back(record);
		return;
	}

	records.push_back(record);
	records.pop_front();
}

template<class T>
deque<T> History<T>::GetRecords()
{
	return records;
}

template<class T>
void History<T>::Update(float dt)
{
	timeCounter += dt;
}