#include "BombsManager.h"

BombsManager::BombsManager(World* world)
{
	this->world = world;
}

BombsManager::~BombsManager()
{
	for (Bomb* bomb : bombs)
	{
		delete bomb;
	}
}

void BombsManager::PutBomb(MatPos bombPos, int length, string playerName)
{
	Bomb* bomb = new Bomb(world, "Assets\\Bomb\\bomb.png", "Assets\\Bomb\\explosion.png");
	bomb->Fire(bombPos, length);
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
