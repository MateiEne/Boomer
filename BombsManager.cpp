#include "BombsManager.h"

BombsManager::BombsManager(World* world, const char* bombFireTexture, const char* bombExplosionTexture, const char* explosionBodyTexture)
{
	this->world = world;

	this->bombFireTexture = _strdup(bombFireTexture);
	this->bombExposionTexture = _strdup(bombExplosionTexture);
	this->explosionBodyTexture = _strdup(explosionBodyTexture);
}

BombsManager::~BombsManager()
{
	delete bombFireTexture;
	delete bombExposionTexture;
	delete explosionBodyTexture;

	for (Bomb* bomb : bombs)
	{
		delete bomb;
	}
}

void BombsManager::PutBomb(MatPos bombPos, int lenght, string playerName)
{
	Bomb* bomb = new Bomb(world, bombFireTexture, bombExposionTexture, explosionBodyTexture);
	bomb->Fire(bombPos, lenght);
	world->PutBomb(bombPos);

	bombs.push_back(bomb);

	mapPlayerBombs[playerName].push_back(bomb);
}

bool BombsManager::CanPutBomb(string playerName, int maxBombs)
{
	return mapPlayerBombs[playerName].size() < maxBombs;
}

void BombsManager::RemoveBombFromMap(Bomb* bomb)
{
	for (auto it = mapPlayerBombs.begin(); it != mapPlayerBombs.end(); it++)
	{
		auto itBomb = find(it->second.begin(), it->second.end(), bomb);
		if (itBomb != it->second.end())
		{
			it->second.erase(itBomb);
			return;
		}
	}
}

void BombsManager::Update(float dt)
{
	if (bombs.empty())
	{
		return;
	}

	if (bombs.front()->HasEnded())
	{
		Bomb* frontBomb = bombs.front();

		MatPos bombPos = frontBomb->GetMatPosition();
		world->RemoveBomb(bombPos);

		bombs.pop_front();

		RemoveBombFromMap(frontBomb);

		delete frontBomb;
	}

	for (Bomb* bomb : bombs)
	{
		bomb->Update(dt);
	}
}

void BombsManager::Draw(sf::RenderWindow& window)
{
	for (Bomb* bomb : bombs)
	{
		bomb->Draw(window);
	}
}
