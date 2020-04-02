#include "World.h"

World::World(
	const char* fileName, 
	const char* tilesTexture,
	vector<MatPos> playerPositions
)
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

	GenerateBoxes();
	RemoveBoxesAroundPlayers(playerPositions);
}

World::~World()
{
}

void World::RemoveBoxesAroundPlayers(vector<MatPos> playersPosition)
{
	for (int i = 0; i < playersPosition.size(); i++)
	{
		// player
		if (map[playersPosition[i].l][playersPosition[i].c] != WALL)
		{
			map[playersPosition[i].l][playersPosition[i].c] = FLOOR;
		}

		// down
		if (map[playersPosition[i].l + 1][playersPosition[i].c] != WALL)
		{
			map[playersPosition[i].l + 1][playersPosition[i].c] = FLOOR;
		}

		// up
		if (map[playersPosition[i].l - 1][playersPosition[i].c] != WALL)
		{
			map[playersPosition[i].l - 1][playersPosition[i].c] = FLOOR;
		}

		// right
		if (map[playersPosition[i].l][playersPosition[i].c + 1] != WALL)
		{
			map[playersPosition[i].l][playersPosition[i].c + 1] = FLOOR;
		}

		// left
		if (map[playersPosition[i].l][playersPosition[i].c - 1] != WALL)
		{
			map[playersPosition[i].l][playersPosition[i].c - 1] = FLOOR;
		}
	}
	return;
}

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

bool World::IsCellEmpty(MatPos pos)
{
	return map[pos.l][pos.c] == FLOOR;
}

bool World::IsCellEmpty(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);
	return map[l][c] == FLOOR;
}

void World::GenerateBoxes()
{
	int l = rand() % (NL);
	int c = rand() % (NC);

	for (int i = 0; i < BOXES_COUNTER; i++)
	{
		if (map[l][c] != FLOOR)
		{
			while (map[l][c] != FLOOR)
			{
				l = rand() % (NL);
				c = rand() % (NC);
			}
		}

		map[l][c] = BOX;
		l = rand() % (NL);
		c = rand() % (NC);
	}
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
