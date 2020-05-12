#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class DrawManager
{
public:
	DrawManager(int width, int height);
	DrawManager(sf::Vector2u size);
	~DrawManager();

	void Clear(sf::Color color = sf::Color(0, 0, 0, 0));
	void Draw(sf::Sprite sprite);

	void Draw(sf::RenderWindow& window);

private:
	sf::RenderTexture texture;
	sf::Sprite sprite;
};

