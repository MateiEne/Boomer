#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Animation
{
public:
	Animation(const char* tag);
	~Animation();

	void Start(float changeFrameTime, bool loop = true);
	void Stop();
	void Update(float dt);
	void AddFrame(sf::IntRect frame);
	bool IsPlaying();
	bool Is(const char* tag);
	sf::IntRect GetCurrentFrame();

private:
	void Init();

	const char* tag;

	float changeFrameTime;
	float timeCounter;

	vector<sf::IntRect> frames;
	int currentFrame;

	bool started;
	bool loop;
};

