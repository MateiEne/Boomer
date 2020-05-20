#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

template<class T>
class Animation
{
public:
	Animation(const char* tag);
	~Animation();

	void Start(float changeFrameTime, bool loop = true);
	void Start(float changeFrameTime, float stopTime);
	void Reset();
	void Stop();
	void Clear();
	void AddFrame(T frame);
	bool IsPlaying();
	bool Is(const char* tag);
	const char* GetTag();
	T GetCurrentFrame();
	int GetCurrentFrameIndex();

	void Update(float dt);

private:
	void Init();

	const char* tag;

	float changeFrameTime;
	float timeCounter;
	float stopTime;
	float stopTimeCounter;

	vector<T> frames;
	int currentFrame;

	bool started;
	bool loop;
	bool isAnimationWithTime;
};


template<class T>
Animation<T>::Animation(const char* tag)
{
	this->tag = tag;
	Init();
}

template<class T>
Animation<T>::~Animation()
{
}

template<class T>
void Animation<T>::Init()
{
	changeFrameTime = 0;
	timeCounter = 0;
	currentFrame = 0;
	isAnimationWithTime = false;
	started = false;
}

template<class T>
void Animation<T>::Start(float changeFrameTime, bool loop)
{
	Init();
	this->changeFrameTime = changeFrameTime;
	this->loop = loop;
	started = true;
}

template<class T>
void Animation<T>::Start(float changeFrameTime, float stopTime)
{
	Init();
	this->changeFrameTime = changeFrameTime;
	this->stopTime = stopTime;
	loop = true;
	stopTimeCounter = 0;
	started = true;
	isAnimationWithTime = true;
}

template<class T>
void Animation<T>::Stop()
{
	currentFrame = 0;
	started = false;
}

template<class T>
void Animation<T>::Reset()
{
	Init();
}

template<class T>
void Animation<T>::AddFrame(T frame)
{
	frames.push_back(frame);
}

template<class T>
T Animation<T>::GetCurrentFrame()
{
	return frames[currentFrame];
}

template<class T>
int Animation<T>::GetCurrentFrameIndex()
{
	return currentFrame;
}

template<class T>
void Animation<T>::Clear()
{
	frames.clear();
	Init();
}

template<class T>
bool Animation<T>::IsPlaying()
{
	return started;
}

template<class T>
bool Animation<T>::Is(const char* tag)
{
	return strcmp(this->tag, tag) == 0;
}

template<class T>
const char* Animation<T>::GetTag()
{
	return tag;
}

template<class T>
void Animation<T>::Update(float dt)
{
	if (!started)
	{
		return;
	}

	timeCounter += dt;

	if (timeCounter >= changeFrameTime)
	{
		timeCounter = 0;
		currentFrame++;
		if (currentFrame == frames.size())
		{
			if (!loop) {
				currentFrame--;	// last frame in vector
				started = false;
				return;
			}

			currentFrame = 0;
		}
	}

	if (isAnimationWithTime)
	{
		stopTimeCounter += dt;
		if (stopTimeCounter >= stopTime)
		{
			started = false;
		}
	}
}