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

void BombsManager::PutBomb(MatPos bombPos, string name)
{
	Bomb* bomb = new Bomb(world, "Assets\\Bomb\\bomb.png", "Assets\\Bomb\\explosion.png");
	bomb->Fire(bombPos, 3);
	world->PutBomb(bombPos);

	bombs.push_back(bomb);
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
