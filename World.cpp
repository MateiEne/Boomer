#include "World.h"

using namespace WorldConst;

World::World(
	const char* fileName, 
	const char* tilesTexture,
	vector<MatPos> playerPositions
)
{
	if (!this->tilesTexture.loadFromFile(tilesTexture))
	{
		cout << "fail tilesTexture";
		exit(-1);
	}

	InitSprite(wallSprite, SpriteSheet::WALL);
	InitSprite(boxSprite, SpriteSheet::BOX);
	InitSprite(floorSprite, SpriteSheet::FLOOR);

	//ReadFromFile(fileName);

	//ReadFromFile(fileName);
	//mazeGenerator.Generate(map, NL, NC);
	mazeGenerator.GenerateTwin(map, NL, NC);
	//mazeGenerator.GenerateTwoSides(map, NL, NC);

	GenerateBoxes();
	RemoveBoxesAroundPlayers(playerPositions);
}

World::~World()
{
}

void World::Restart(vector<MatPos> playerPositions)
{
	mazeGenerator.GenerateTwin(map, NL, NC);
	GenerateBoxes();
	RemoveBoxesAroundPlayers(playerPositions);
}

void World::PutBomb(MatPos pos)
{
	map[pos.l][pos.c] = BOMB;
}

bool World::IsCellMarkedAsExplosionDanger(MatPos pos)
{
	return map[pos.l][pos.c] == EXPLOSION_DANGER;
}

bool World::IsCellBomb(MatPos pos)
{
	return map[pos.l][pos.c] == BOMB;
}

bool World::IsCellMarkedAsExplosion(MatPos pos)
{
	return map[pos.l][pos.c] == EXPLOSION;
}

bool World::IsCellMarkedAsExplosion(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);
	return map[l][c] == EXPLOSION;
}

bool World::IsCellBomb(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);
	return map[l][c] == BOMB;
}


void World::MarkExplosionBody(MatPos pos, char ch)
{
	map[pos.l][pos.c] = ch;
}

void World::RemoveExplosion(MatPos pos)
{
	map[pos.l][pos.c] = FLOOR;
}

void World::RemoveBomb(MatPos pos)
{
	map[pos.l][pos.c] = FLOOR;
}

void World::RemoveBox(MatPos pos)
{
	map[pos.l][pos.c] = FLOOR;
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

void World::PrintMap()
{
	for (int i = 0; i < NL; i++)
	{
		for (int j = 0; j < NC; j++)
		{
			cout << map[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
}

void World::ReadFromFile(const char* fileName)
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

void World::InitSprite(sf::Sprite& sprite, MatPos pos)
{
	sprite.setTexture(this->tilesTexture);
	sprite.setTextureRect(
		sf::IntRect(
			pos.c * SpriteSheet::FRAME_WIDTH,
			pos.l * SpriteSheet::FRAME_HEIGHT,
			SpriteSheet::FRAME_WIDTH,
			SpriteSheet::FRAME_HEIGHT
		)
	);
	sprite.setScale(
		CELL_WIDTH / SpriteSheet::FRAME_WIDTH, 
		CELL_HEIGHT / SpriteSheet::FRAME_HEIGHT
	);
}

bool World::IsCellEmpty(MatPos pos)
{
	return map[pos.l][pos.c] == FLOOR;
}

bool World::IsCellEmpty(int l, int c)
{
	return map[l][c] == FLOOR;
}

bool World::IsCellEmpty(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);
	return map[l][c] == FLOOR;
}

bool World::IsCellBox(MatPos pos)
{
	return map[pos.l][pos.c] == BOX;
}

bool World::IsCellBox(int l, int c)
{
	return map[l][c] == BOX;
}

bool World::IsCellBox(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);
	return map[l][c] == BOX;
}

bool World::IsCellWall(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);
	return map[l][c] == WALL;
}

bool World::IsCellWall(MatPos pos)
{
	return map[pos.l][pos.c] == WALL;
}

bool World::IsCellWall(int l, int c)
{
	return map[l][c] == WALL;
}

bool World::CanPutBomb(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);

	return map[l][c] == FLOOR || map[l][c] == EXPLOSION_DANGER || map[l][c] == EXPLOSION;
}

void World::GenerateBoxes()
{
	int l = rand() % (NL);
	int c = rand() % (NC);

	for (int i = 0; i < BOX_COUNT; i++)
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

void World::Update(float dt)
{
	//PrintMap();
}

void World::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < NL; i++)
	{
		for (int j = 0; j < NC; j++)
		{
			switch (map[i][j])
			{
			case WALL:
				wallSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(wallSprite);
				break;

			case BOX:
				boxSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(boxSprite);
				break;

			case BOMB:
				floorSprite.setColor(sf::Color::White);
				floorSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(floorSprite);

				floorSprite.setColor(sf::Color(0, 0, 0, 100));
				window.draw(floorSprite);
				break;

			case EXPLOSION_DANGER:
				floorSprite.setColor(sf::Color::White);
				floorSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(floorSprite);

				floorSprite.setColor(sf::Color(120, 0, 0, 100));
				window.draw(floorSprite);
				break;

			case EXPLOSION:
				floorSprite.setColor(sf::Color::White);
				floorSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(floorSprite);

				floorSprite.setColor(sf::Color(255, 0, 0, 100));
				window.draw(floorSprite);
				break;

			default:
				floorSprite.setColor(sf::Color::White);
				floorSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(floorSprite);
				break;
			}
		}
	}
}
