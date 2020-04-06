#include "Bomb.h"

Bomb::Bomb(const char* bombTexture, const char* explosionTexture, MatPos pos) :
	fireAnimation{ BombConst::SpriteSheet::Fire::TAG },
	explosionAnimation{ ExplosionConst::SpriteSheet::TAG }
{
	if (!this->bombTexture.loadFromFile(bombTexture))
	{
		cout << "error loading bomb spriteSheetTexture";
		exit(-1);
	}

	if (!this->explosionTexture.loadFromFile(explosionTexture))
	{
		cout << "error loading explosion spriteSheetTexture";
		exit(-1);
	}

	InitBombSprite();
	InitAnimation(
		fireAnimation, 
		BombConst::SpriteSheet::Fire::COUNT, 
		BombConst::SpriteSheet::Fire::FRAMES, 
		BombConst::SpriteSheet::FRAME_WIDTH, 
		BombConst::SpriteSheet::FRAME_HEIGHT
	);

	InitAnimation(
		explosionAnimation,
		ExplosionConst::SpriteSheet::COUNT,
		ExplosionConst::SpriteSheet::CENTER,
		ExplosionConst::SpriteSheet::FRAME_WIDTH,
		ExplosionConst::SpriteSheet::FRAME_HEIGHT
	);

	matPos = pos;
	exploted = false;

	fireAnimation.Start(BombConst::SpriteSheet::Fire::TIME_FRAME_CHANGE_COUNT);
}

Bomb::~Bomb()
{
}

void Bomb::InitBombSprite()
{
	bombSprite.setTexture(bombTexture);
	bombSprite.setTextureRect(
		sf::IntRect(
			BombConst::SpriteSheet::DEFAULT_FRAME.c * BombConst::SpriteSheet::FRAME_WIDTH,
			BombConst::SpriteSheet::DEFAULT_FRAME.l * BombConst::SpriteSheet::FRAME_HEIGHT,
			BombConst::SpriteSheet::FRAME_WIDTH,
			BombConst::SpriteSheet::FRAME_HEIGHT
		)
	);
	bombSprite.setScale(
		WorldConst::CELL_WIDTH / BombConst::SpriteSheet::FRAME_WIDTH,
		WorldConst::CELL_HEIGHT / BombConst::SpriteSheet::FRAME_HEIGHT
	);
}

void Bomb::InitAnimation(
	Animation& animation, 
	const int count, 
	const MatPos frames[], 
	const float frameWidth, 
	const float frameHeight
)
{
	for (int i = 0; i < count; i++)
	{
		animation.AddFrame(
			sf::IntRect(
				frames[i].c * frameWidth,
				frames[i].l * frameHeight,
				frameWidth,
				frameHeight
			)
		);
	}
}

void Bomb::Update(float dt)
{
	fireAnimation.Update(dt);
	explosionAnimation.Update(dt);

	if (fireAnimation.GetCurrentFrameIndex() >= BombConst::SpriteSheet::Fire::FRAME_START_EXPLOSION)
	{
		if (!exploted)
		{
			explosionAnimation.Start(ExplosionConst::SpriteSheet::TIME_FRAME_CHANGE_COUNT, false);
			exploted = true;
		}
	}
	else
	{
		exploted = false;
	}
}

void Bomb::Draw(sf::RenderWindow& window)
{
	if (explosionAnimation.IsPlaying())
	{
		int explosionIndex = explosionAnimation.GetCurrentFrameIndex();

		DrawExplosionFrame(window, matPos, ExplosionConst::SpriteSheet::CENTER[explosionIndex]);
		DrawYSide(window, 3, true, explosionIndex);
		DrawYSide(window, 3, false, explosionIndex);
		DrawXSide(window, 3, true, explosionIndex);
		DrawXSide(window, 3, false, explosionIndex);
	}


	bombSprite.setPosition(matPos.c  * WorldConst::CELL_WIDTH, matPos.l * WorldConst::CELL_HEIGHT);
	bombSprite.setTextureRect(fireAnimation.GetCurrentFrame());
	window.draw(bombSprite);
}

void Bomb::DrawSpriteAt(sf::RenderWindow& window, sf::Sprite& sprite, MatPos pos)
{
	sprite.setPosition(pos.c  * WorldConst::CELL_WIDTH, pos.l * WorldConst::CELL_HEIGHT);
	window.draw(sprite);
}

void Bomb::DrawExplosionFrame(sf::RenderWindow& window, MatPos pos, MatPos sheetPos)
{
	sf::Sprite sprite(
		explosionTexture,
		sf::IntRect(
			sheetPos.c * ExplosionConst::SpriteSheet::FRAME_WIDTH,
			sheetPos.l * ExplosionConst::SpriteSheet::FRAME_HEIGHT,
			ExplosionConst::SpriteSheet::FRAME_WIDTH,
			ExplosionConst::SpriteSheet::FRAME_HEIGHT
		)
	);

	sprite.setScale(
		WorldConst::CELL_WIDTH / ExplosionConst::SpriteSheet::FRAME_WIDTH,
		WorldConst::CELL_HEIGHT / ExplosionConst::SpriteSheet::FRAME_HEIGHT
	);

	DrawSpriteAt(window, sprite, pos);
}

void Bomb::DrawYSide(sf::RenderWindow& window, int length, bool up, int explosionIndex)
{
	int sign = up ? -1 : 1;

	MatPos pos = matPos;
	pos.l += 1 * sign;

	// Side
	while (length > 1)
	{
		DrawExplosionFrame(window, pos, ExplosionConst::SpriteSheet::SIDE_Y[explosionIndex]);

		length--;
		pos.l += 1 * sign;
	}

	// Peak
	if (up) {
		DrawExplosionFrame(window, pos, ExplosionConst::SpriteSheet::PEAK_UP[explosionIndex]);
	}
	else
	{
		DrawExplosionFrame(window, pos, ExplosionConst::SpriteSheet::PEAK_DOWN[explosionIndex]);
	}
}

void Bomb::DrawXSide(sf::RenderWindow& window, int length, bool right, int explosionIndex)
{
	int sign = right ? 1 : -1;

	MatPos pos = matPos;
	pos.c += 1 * sign;

	// Side
	while (length > 1)
	{
		DrawExplosionFrame(window, pos, ExplosionConst::SpriteSheet::SIDE_X[explosionIndex]);

		length--;
		pos.c += 1 * sign;
	}

	// Peak
	if (right) {
		DrawExplosionFrame(window, pos, ExplosionConst::SpriteSheet::PEAK_RIGHT[explosionIndex]);
	}
	else
	{
		DrawExplosionFrame(window, pos, ExplosionConst::SpriteSheet::PEAK_LEFT[explosionIndex]);
	}
}