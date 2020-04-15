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

Bomb* BombsManager::PutBomb(MatPos bombPos)
{
	Bomb* bomb = new Bomb(world, "Assets\\Bomb\\bomb.png", "Assets\\Bomb\\explosion.png");
	//bomb->Fire(bombPos, 3);
	//world->PutBomb(bombPos);

	//bombs.push_back(bomb);

	return bomb;
}

void BombsManager::Update(float dt)
{
	/*if (bombs.empty())
	{
		return;
	}

	if (bombs.front()->HasEnded())
	{
		MatPos bombPos = bombs.front()->GetMatPosition();
		world->RemoveBomb(bombPos);

		Bomb* bomb = bombs.front();
		bombs.pop_front();

		delete bomb;

		bomb = nullptr;
	}

	for (Bomb* bomb : bombs)
	{
		bomb->Update(dt);
	}*/
}

void BombsManager::Draw(sf::RenderWindow& window)
{
	/*for (Bomb* bomb : bombs)
	{
		bomb->Draw(window);
	}*/
}
