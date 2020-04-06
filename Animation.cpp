#include "Animation.h"

Animation::Animation(const char* tag)
{
	this->tag = tag;
	Init();
}

Animation::~Animation()
{
}

void Animation::Init()
{
	changeFrameTime = 0;
	timeCounter = 0;
	currentFrame = 0;
	isAnimationWithTime = false;
	started = false;
}

void Animation::Start(float changeFrameTime, bool loop)
{
	Init();
	this->changeFrameTime = changeFrameTime;
	this->loop = loop;
	started = true;
}

void Animation::Start(float changeFrameTime, float stopTime)
{
	Init();
	this->changeFrameTime = changeFrameTime;
	this->stopTime = stopTime;
	loop = true;
	stopTimeCounter = 0;
	started = true;
	isAnimationWithTime = true;
}

void Animation::Stop()
{
	currentFrame = 0;
	started = false;
}

void Animation::AddFrame(sf::IntRect frame)
{
	frames.push_back(frame);
}

sf::IntRect Animation::GetCurrentFrame()
{
	return frames[currentFrame];
}

int Animation::GetCurrentFrameIndex()
{
	return currentFrame;
}

bool Animation::IsPlaying()
{
	return started;
}

bool Animation::Is(const char* tag)
{
	return strcmp(this->tag, tag) == 0;
}

void Animation::Update(float dt) 
{
	if (!started) {
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