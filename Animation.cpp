#include "Animation.h"

Animation::Animation()
{
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
	started = false;
}

void Animation::Start(float changeFrameTime)
{
	this->changeFrameTime = changeFrameTime;
	started = true;
}

void Animation::Stop()
{
	started = false;
	Init();
}

void Animation::AddFrame(sf::IntRect frame)
{
	frames.push_back(frame);
}

sf::IntRect Animation::GetCurrentFrame()
{
	return frames[currentFrame];
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
			currentFrame = 0;
		}
	}
}