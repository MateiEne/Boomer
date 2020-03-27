#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Animation
{
public:
	Animation();
	~Animation();

	void Start(float changeFrameTime);
	void Stop();
	void Update(float dt);
	void AddFrame(sf::IntRect frame);
	sf::IntRect GetCurrentFrame();

private:
	void Init();
	float changeFrameTime;
	float timeCounter;

	vector<sf::IntRect> frames;
	int currentFrame;

	bool started;
};

