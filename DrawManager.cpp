#include "DrawManager.h"



DrawManager::DrawManager(int width, int height, bool enableDebug)
{
	this->enableDebug = enableDebug;

	for (Layer l : LAYERS_ORDER)
	{
		if (!enableDebug && l == Layer::DEBUG)
		{
			continue;
		}

		sf::RenderTexture* texture = new sf::RenderTexture();
		texture->create(width, height);

		layerTexture.insert(pair<Layer, sf::RenderTexture*>(l, texture));
	}
}

DrawManager::DrawManager(sf::Vector2u size, bool enableDebug) :
	DrawManager(size.x, size.y, enableDebug)
{
}

DrawManager::~DrawManager()
{
	for (Layer l : LAYERS_ORDER)
	{
		if (!enableDebug && l == Layer::DEBUG)
		{
			continue;
		}

		sf::RenderTexture* texture = layerTexture[l];
		delete texture;

		layerTexture.erase(l);
	}
} 

void DrawManager::Clear(sf::Color color)
{
	// Clear the whole texture with the given color
	for (Layer l : LAYERS_ORDER)
	{
		if (!enableDebug && l == Layer::DEBUG)
		{
			continue;
		}

		layerTexture[l]->clear(color);
	}
}

void DrawManager::Draw(sf::Sprite sprite, Layer layer)
{
	if (!enableDebug && layer == Layer::DEBUG)
	{
		return;
	}

	layerTexture[layer]->draw(sprite);
}

void DrawManager::Draw(sf::RenderWindow& window)
{
	for (Layer l : LAYERS_ORDER)
	{
		if (!enableDebug && l == Layer::DEBUG)
		{
			continue;
		}

		// We're done drawing to the texture
		layerTexture[l]->display();

		// Draw the texture
		sprite.setTexture(layerTexture[l]->getTexture());
		window.draw(sprite);
	}
}