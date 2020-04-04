#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Animation
{
public:
	Animation();
	~Animation();

	void Start(float changeFrameTime, bool loop = true);
	void Start(float changeFrameTime, float stopTime);
	void Stop();
	void Update(float dt);
	void AddFrame(sf::IntRect frame);
	bool IsPlaying();
	sf::IntRect GetCurrentFrame();

private:
	void Init();


	float changeFrameTime;
	float timeCounter;
	float stopTime;
	float stopTimeCounter;

	vector<sf::IntRect> frames;
	int currentFrame;

	bool started;
	bool loop;
	bool isAnimationWithTime;
};

