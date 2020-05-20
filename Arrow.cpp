#include "Arrow.h"

using namespace ArrowConst;

Arrow::Arrow(World* world, const char* texture)
{
	if (!spriteSheetTexture.loadFromFile(texture))
	{
		cout << "error loading player spriteSheetTexture";
		exit(-1);
	}

	this->world = world;

	started = false;

	direction = Direction::RIGHT;
}

void Arrow::Shoot(MatPos pos, Direction dir)
{
	started = true;

	direction = dir;

	position.x = pos.c * WorldConst::CELL_WIDTH;
	position.y = pos.l * WorldConst::CELL_HEIGHT;

	frame = GetFrame(dir);
	InitSprite();
}


sf::IntRect Arrow::GetFrame(Direction dir)
{
	MatPos arrowFrame;
	switch (dir)
	{
	case Direction::RIGHT:
		arrowFrame = SpriteSheet::Right::FRAME;
		break;

	case Direction::LEFT:
		arrowFrame = SpriteSheet::Left::FRAME;
		break;

	case Direction::DOWN:
		arrowFrame = SpriteSheet::Down::FRAME;
		break;

	case Direction::UP:
		arrowFrame = SpriteSheet::Up::FRAME;
		break;
	}

	return sf::IntRect(
		arrowFrame.c * SpriteSheet::FRAME_WIDTH,
		arrowFrame.l * SpriteSheet::FRAME_HEIGHT,
		SpriteSheet::FRAME_WIDTH,
		SpriteSheet::FRAME_HEIGHT
	);;
}

void Arrow::InitSprite()
{
	sprite.setTexture(spriteSheetTexture);
	sprite.setTextureRect(frame);
	sprite.setScale(
		WorldConst::CELL_WIDTH / SpriteSheet::FRAME_WIDTH,
		WorldConst::CELL_HEIGHT / SpriteSheet::FRAME_HEIGHT
	);
}

void Arrow::Update(float dt)
{
	if (!started) 
	{
		return;
	}

	switch (direction)
	{
	case Direction::RIGHT:
		position.x += SPEED * dt;
		break;

	case Direction::LEFT:
		position.x -= SPEED * dt;
		break;

	case Direction::DOWN:
		position.y += SPEED * dt;
		break;

	case Direction::UP:
		position.y -= SPEED * dt;
		break;
	}
}

void Arrow::Draw(DrawManager& drawManager)
{
	if (!started)
	{
		return;
	}

	sprite.setPosition(position + sf::Vector2f(0, -WorldConst::BASE_GROUND));
	sprite.setTextureRect(frame);
	drawManager.Draw(sprite, Layer::FRONT);
}