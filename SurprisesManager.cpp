#include "SurprisesManager.h"

using namespace SurprisesConst;
using namespace WorldConst;

SurprisesManager::SurprisesManager(World* world, const char* texture)
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
	InitSprite(blastRadiusSurpriseSprite, SurpriseSprite::BLAST_RADIUS);
	InitSprite(speedSurpriseSprite, SurpriseSprite::SPEED);
	InitSprite(invincibleSurpriseSprite, SurpriseSprite::INVINCIBLE);
	//InitSprite();

	//PrintSurpriseMap();

	InitSurpriseMap();

	GenerateSurprises();
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

void SurprisesManager::InitSurpriseMap()
{
	for (int i = 0; i < NL; i++)
	{
		for (int j = 0; j < NC; j++)
		{
			surpriseMap[i][j] = SurpriseType::NONE;
		}
	}
}

void SurprisesManager::PrintSurpriseMap()
{
	for (int i = 0; i < NL; i++)
	{
		for (int j = 0; j < NC; j++)
		{
			cout << surpriseMap[i][j] << " ";
		}
		cout << endl;
	}
}

void SurprisesManager::GenerateInvincibleSurprises()
{
	int l, c;

	for (int i = (4 * SURPRISE_COUNT) / 5; i < SURPRISE_COUNT; i++)
	{
		l = rand() % (NL);
		c = rand() % (NC);

		while (!world->IsCellBox(l, c) || surpriseMap[l][c] != SurpriseType::NONE)
		{
			l = rand() % (NL);
			c = rand() % (NC);
		}

		surpriseMap[l][c] = SurpriseType::INVINCIBLE;
	}
}

void SurprisesManager::GenerateSpeedSurprises()
{
	int l, c;

	for (int i = (3 * SURPRISE_COUNT) / 5; i < (4 * SURPRISE_COUNT) / 5; i++)
	{
		l = rand() % (NL);
		c = rand() % (NC);

		while (!world->IsCellBox(l, c) || surpriseMap[l][c] != SurpriseType::NONE)
		{
			l = rand() % (NL);
			c = rand() % (NC);
		}

		surpriseMap[l][c] = SurpriseType::SPEED;
	}
}

void SurprisesManager::GenerateBlastRadiusSurprises()
{
	int l, c;

	for (int i = (2 * SURPRISE_COUNT) / 5; i < (3 * SURPRISE_COUNT) / 5; i++)
	{
		l = rand() % (NL);
		c = rand() % (NC);

		while (!world->IsCellBox(l, c) || surpriseMap[l][c] != SurpriseType::NONE)
		{
			l = rand() % (NL);
			c = rand() % (NC);
		}

		surpriseMap[l][c] = SurpriseType::BLAST_RADIUS;
	}

}

void SurprisesManager::GenerateBombsSupplySurprises()
{
	int l, c;

	for (int i = SURPRISE_COUNT / 5; i < (2 * SURPRISE_COUNT) / 5; i++)
	{
		l = rand() % (NL);
		c = rand() % (NC);

		while (!world->IsCellBox(l, c) || surpriseMap[l][c] != SurpriseType::NONE)
		{
			l = rand() % (NL);
			c = rand() % (NC);
		}

		surpriseMap[l][c] = SurpriseType::BOMBS_SUPPLY;
	}

}

void SurprisesManager::GenerateRandomSurprises()
{
	int l, c;

	for (int i = 0; i < SURPRISE_COUNT / 5; i++)
	{
		l = rand() % (NL);
		c = rand() % (NC);

		while (!world->IsCellBox(l, c))
		{
			l = rand() % (NL);
			c = rand() % (NC);
		}

		surpriseMap[l][c] = SurpriseType::RANDOM;
	}
}

void SurprisesManager::GenerateSurprises()
{
	GenerateBlastRadiusSurprises();
	GenerateBombsSupplySurprises();
	GenerateRandomSurprises();
	GenerateSpeedSurprises();
	GenerateInvincibleSurprises();
}

bool SurprisesManager::IsCellASurprise(sf::Vector2f worldPos)
{
	return IsCellBombsSupplySurprise(worldPos) ||
		IsCellRandomSurprise(worldPos) ||
		IsCellBlastIncreaseSupply(worldPos) ||
		IsCellSpeedSurprise(worldPos) ||
		IsCellInvincibleSurprise(worldPos);
}

bool SurprisesManager::IsCellInvincibleSurprise(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);

	return surpriseMap[l][c] == SurpriseType::INVINCIBLE;
}

bool SurprisesManager::IsCellSpeedSurprise(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);

	return surpriseMap[l][c] == SurpriseType::SPEED;
}

bool SurprisesManager::IsCellBlastIncreaseSupply(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);

	return surpriseMap[l][c] == SurpriseType::BLAST_RADIUS;
}

bool SurprisesManager::IsCellRandomSurprise(MatPos pos)
{
	return surpriseMap[pos.l][pos.c] == SurpriseType::RANDOM;
}

bool SurprisesManager::IsCellRandomSurprise(int l, int c)
{
	return surpriseMap[l][c] == SurpriseType::RANDOM;
}

bool SurprisesManager::IsCellRandomSurprise(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);

	return surpriseMap[l][c] == SurpriseType::RANDOM;
}

bool SurprisesManager::IsCellBombsSupplySurprise(MatPos pos)
{
	return surpriseMap[pos.l][pos.c] == SurpriseType::BOMBS_SUPPLY;
}

bool SurprisesManager::IsCellBombsSupplySurprise(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);

	return surpriseMap[l][c] == SurpriseType::BOMBS_SUPPLY;
}

void SurprisesManager::RemoveSurpriseFromMap(MatPos pos)
{
	surpriseMap[pos.l][pos.c] = SurpriseType::NONE;
}

void SurprisesManager::RemoveSurpriseFromMap(int l, int c)
{
	surpriseMap[l][c] = SurpriseType::NONE;
}

void SurprisesManager::RemoveSurpriseFromMap(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);

	surpriseMap[l][c] = SurpriseType::NONE;
}

SurpriseType SurprisesManager::GetSurprise(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);

	return surpriseMap[l][c];
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
			if (surpriseMap[i][j] == SurpriseType::RANDOM && !world->IsCellBox(i, j))
			{
				randomSurpriseSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(randomSurpriseSprite);
			}
			else if (surpriseMap[i][j] == SurpriseType::BOMBS_SUPPLY && !world->IsCellBox(i, j))
			{
				bombSupplySurpriseSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(bombSupplySurpriseSprite);
			}
			else if (surpriseMap[i][j] == SurpriseType::BLAST_RADIUS && !world->IsCellBox(i, j))
			{
				blastRadiusSurpriseSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(blastRadiusSurpriseSprite);
			}
			else if (surpriseMap[i][j] == SurpriseType::SPEED && !world->IsCellBox(i, j))
			{
				speedSurpriseSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(speedSurpriseSprite);
			}
			else if (surpriseMap[i][j] == SurpriseType::INVINCIBLE && !world->IsCellBox(i, j))
			{
				invincibleSurpriseSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				window.draw(invincibleSurpriseSprite);
			}
		}
	}
}