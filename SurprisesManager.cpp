#include "SurprisesManager.h"
#include "SurprisesManager.h"

using namespace WorldConst;

SurprisesManager::SurprisesManager(World* world, const char* texture, const char* fileName)
{
	if (!this->texture.loadFromFile(texture))
	{
		cout << "error loading surpriseTexture";
		exit(-1);
	}

	srand(time(NULL));

	this->world = world;

	InitSprite(randomSurpriseSprite, SurpriseSprite::RANDOM);
	InitSprite(bombSupplySurpriseSprite, SurpriseSprite::BOMB_SUPPLY);
	//InitSprite();

	GenerateSurprises();
	PrintSurpriseMap();
}

void SurprisesManager::InitSprite(sf::Sprite& sprite, MatPos pos)
{
	sprite.setTexture(this->texture);
	sprite.setTextureRect(
		sf::IntRect(
			pos.c * SurpriseSprite::FRAME_WIDTH,
			pos.l * SurpriseSprite::FRAME_HEIGHT,
			SurpriseSprite::FRAME_WIDTH,
			SurpriseSprite::FRAME_HEIGHT
		)
	);
	sprite.setScale(
		CELL_WIDTH / SurpriseSprite::FRAME_WIDTH,
		CELL_HEIGHT / SurpriseSprite::FRAME_HEIGHT
	);
}

void SurprisesManager::InitSprite()
{
	randomSurpriseSprite.setTexture(this->texture);
	randomSurpriseSprite.setTextureRect(
		sf::IntRect(
			SurpriseSprite::RANDOM.c * SurpriseSprite::FRAME_WIDTH,
			SurpriseSprite::RANDOM.l * SurpriseSprite::FRAME_HEIGHT,
			SurpriseSprite::FRAME_WIDTH,
			SurpriseSprite::FRAME_HEIGHT
		)
	);
	randomSurpriseSprite.setScale(
		CELL_WIDTH / SurpriseSprite::FRAME_WIDTH,
		CELL_HEIGHT / SurpriseSprite::FRAME_HEIGHT
	);
}

void SurprisesManager::ReadFromFile(const char* fileName)
{
	ifstream f(fileName);

	for (int i = 0; i < NL; i++)
	{
		for (int j = 0; j < NC; j++)
		{
			f >> surpriseMap[i][j];
		}
	}
}

void SurprisesManager::PrintSurpriseMap()
{
	for (int i = 0; i < NL; i++)
	{
		for (int j = 0; j < NC; j++)
		{
			if (surpriseMap[i][j] == RANDOM_SURPRISE)
			{
				cout << RANDOM_SURPRISE << " ";
			}
			else if (surpriseMap[i][j] == SUPPLY_BOMB_SURPRISE)
			{
				cout << SUPPLY_BOMB_SURPRISE << " ";
			}
			else
			{
				cout << ". ";
			}
		}
		cout << endl;
	}
}

void SurprisesManager::GenerateSurprises()
{
	int l, c;

	for (int i = 0; i < SURPRISE_COUNT / 2; i++)
	{
		l = rand() % (NL);
		c = rand() % (NC);

		while (!world->IsCellBox(l, c))
		{
			l = rand() % (NL);
			c = rand() % (NC);
		}

		surpriseMap[l][c] = RANDOM_SURPRISE;
	}

	for (int i = SURPRISE_COUNT / 2; i < SURPRISE_COUNT; i++)
	{
		l = rand() % (NL);
		c = rand() % (NC);

		while (!world->IsCellBox(l, c) ||
			(!world->IsCellBox(l, c) && surpriseMap[l][c] == RANDOM_SURPRISE))
		{
			l = rand() % (NL);
			c = rand() % (NC);
		}
		
		cout << l << " " << c << endl;

		surpriseMap[l][c] = SUPPLY_BOMB_SURPRISE;
	}
}

bool SurprisesManager::IsCellRandomSurprise(MatPos pos)
{
	return surpriseMap[pos.l][pos.c] == RANDOM_SURPRISE;
}

bool SurprisesManager::IsCellRandomSurprise(int l, int c)
{
	return surpriseMap[l][c] == RANDOM_SURPRISE;
}

void SurprisesManager::Update(float dt)
{
}

void SurprisesManager::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < NL; i++)
	{
		for (int j = 0; j < NC; j++)
		{
			if (
				surpriseMap[i][j] == RANDOM_SURPRISE && 
				!world->IsCellBox(i, j) && 
				!world->IsCellWall(i, j)
			)
			{
				randomSurpriseSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(randomSurpriseSprite);
			}
			else if (
				surpriseMap[i][j] == SUPPLY_BOMB_SURPRISE &&
				!world->IsCellBox(i, j) &&
				!world->IsCellWall(i, j)
				)
			{
				bombSupplySurpriseSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(bombSupplySurpriseSprite);
			}
		}
	}
}