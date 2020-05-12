#include "DrawManager.h"



DrawManager::DrawManager(int width, int height)
{
	texture.create(width, height);
}

DrawManager::DrawManager(sf::Vector2u size)
{
	texture.create(size.x, size.y);
}

DrawManager::~DrawManager()
{
}

void DrawManager::Clear(sf::Color color)
{
	// Clear the whole texture with the given color
	texture.clear(color);
}

void DrawManager::Draw(sf::Sprite sprite)
{
	texture.draw(sprite);
}

void DrawManager::Draw(sf::RenderWindow& window)
{
	// We're done drawing to the texture
	texture.display();

	// Draw the texture
	sprite.setTexture(texture.getTexture());
	window.draw(sprite);
}