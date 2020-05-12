#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <map>
#include <iostream>

using namespace std;

enum class Layer
{
	BACK,
	FRONT,
	DEBUG
};

const list<Layer> LAYERS_ORDER{
	Layer::BACK,
	Layer::FRONT,
	Layer::DEBUG
};

class DrawManager
{
public:
	DrawManager(int width, int height, bool enableDebug);
	DrawManager(sf::Vector2u size, bool enableDebug);
	~DrawManager();

	void Clear(sf::Color color = sf::Color::Transparent);
	void Draw(sf::Sprite sprite, Layer layer);

	void Draw(sf::RenderWindow& window);

private:
	map<Layer, sf::RenderTexture*> layerTexture;
	sf::Sprite sprite;

	bool enableDebug;
};

