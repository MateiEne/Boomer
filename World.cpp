#include "World.h"

World::World(const char* fileName, const char* tilesTexture)
{
	ReadFromFIle(fileName);

	if (!this->tilesTexture.loadFromFile(tilesTexture))
	{
		cout << "fail tilesTexture";
		exit(-1);
	}

	InitSprite(wallSprite, TILE_WALL_C, TILE_WALL_L);
	InitSprite(boxSprite, TILE_BOX_C, TILE_BOX_L);
	InitSprite(floorSprite, TILE_FLOOR_C, TILE_FLOOR_L);
}

//public methods

World::~World()
{
}

void World::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < NL; i++)
	{
		for (int j = 0; j < NC; j++)
		{
			if (map[i][j] == WALL)
			{
				wallSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(wallSprite);
			}
			else if (map[i][j] == BOX)
			{
				boxSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(boxSprite);
			}
			else if (map[i][j] == FLOOR)
			{
				floorSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(floorSprite);
			}
		}
	}

}

//private methods

void World::ReadFromFIle(const char* fileName)
{
	ifstream f(fileName);

	for (int i = 0; i < NL; i++)
	{
		for (int j = 0; j < NC; j++)
		{
			f >> map[i][j];
		}
	}
}

void World::InitSprite(sf::Sprite& sprite, int c, int l)
{
	sprite.setTexture(this->tilesTexture);
	sprite.setTextureRect(
		sf::IntRect(
			c * TILE_WIDTH,
			l * TILE_HEIGHT,
			TILE_WIDTH,
			TILE_HEIGHT
		)
	);
	sprite.setScale(CELL_WIDTH / TILE_WIDTH, CELL_HEIGHT / TILE_HEIGHT);
}