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

void SurprisesManager::GenerateSurprises(SurpriseType surprise, float probability)
{
	int l, c;

	for (int i = 0; i < SURPRISE_COUNT * probability; i++)
	{
		l = rand() % (NL);
		c = rand() % (NC);

		while (!world->IsCellBox(l, c))
		{
			l = rand() % (NL);
			c = rand() % (NC);
		}

		surpriseMap[l][c] = surprise;
	}
}

void SurprisesManager::GenerateSurprises()
{
	GenerateSurprises(SurpriseType::BLAST_RADIUS, SurpriseProbabity::BLAST_RADIUS);
	GenerateSurprises(SurpriseType::BOMBS_SUPPLY, SurpriseProbabity::BOMBS_SUPPLY);
	GenerateSurprises(SurpriseType::INVINCIBLE, SurpriseProbabity::INVINCIBLE);
	GenerateSurprises(SurpriseType::RANDOM, SurpriseProbabity::RANDOM);
	GenerateSurprises(SurpriseType::SPEED, SurpriseProbabity::SPEED);
}

bool SurprisesManager::IsCellASurprise(sf::Vector2f worldPos)
{
	return !IsCellNoneSurprise(worldPos);
}

bool SurprisesManager::IsCellNoneSurprise(sf::Vector2f worldPos)
{
	int l = (int)((worldPos.y + CELL_HEIGHT / 2) / CELL_HEIGHT);
	int c = (int)((worldPos.x + CELL_WIDTH / 2) / CELL_WIDTH);

	return surpriseMap[l][c] == SurpriseType::NONE;
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

void SurprisesManager::Draw(DrawManager& drawManager)
{
	for (int i = 0; i < NL; i++)
	{
		for (int j = 0; j < NC; j++)
		{
			if (world->IsCellBox(i, j))
			{
				continue;
			}
			
			switch (surpriseMap[i][j])
			{
			case SurpriseType::RANDOM:
				randomSurpriseSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				drawManager.Draw(randomSurpriseSprite, Layer::BACK);
				break;

			case SurpriseType::BOMBS_SUPPLY:
				bombSupplySurpriseSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				drawManager.Draw(bombSupplySurpriseSprite, Layer::BACK);
				break;

			case SurpriseType::BLAST_RADIUS:
				blastRadiusSurpriseSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				drawManager.Draw(blastRadiusSurpriseSprite, Layer::BACK);
				break;

			case SurpriseType::SPEED:
				speedSurpriseSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				drawManager.Draw(speedSurpriseSprite, Layer::BACK);
				break;
					
			case SurpriseType::INVINCIBLE:
				invincibleSurpriseSprite.setPosition(j * CELL_WIDTH, i * CELL_HEIGHT);
				drawManager.Draw(invincibleSurpriseSprite, Layer::BACK);
				break;

			default:
				break;
			}
		}
	}
}