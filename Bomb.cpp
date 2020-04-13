#include "Bomb.h"

Bomb::Bomb(World* world, const char* bombTexture, const char* explosionTexture) :
	fireAnimation{ BombConst::SpriteSheet::Fire::TAG },
	explosionAnimation{ ExplosionConst::SpriteSheet::TAG },
	increaseLengthAnimation{ ExplosionConst::LengthAnimation::TAG },
	decreaseLengthAnimation{ ExplosionConst::LengthAnimation::TAG },
	peakLengthAnimation{ ExplosionConst::LengthAnimation::TAG }
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

	this->world = world;

	InitBombSprite();
	InitAnimation(
		fireAnimation, 
		BombConst::SpriteSheet::Fire::COUNT, 
		BombConst::SpriteSheet::Fire::FRAMES, 
		BombConst::SpriteSheet::FRAME_WIDTH, 
		BombConst::SpriteSheet::FRAME_HEIGHT
	);

	InitExplosionAnimation();
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
	Animation<sf::IntRect>& animation,
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

void Bomb::InitExplosionAnimation()
{
	// animation just with the indexes from the array with frames positions in the sprite sheet
	for (int i = 0; i < ExplosionConst::SpriteSheet::COUNT; i++)
	{
		explosionAnimation.AddFrame(i);
	}
}

void Bomb::InitLengthAnimation()
{
	// increase length: from length 1 -> (length - 1)
	// exception: length == 1
	if (length == 1)
	{
		increaseLengthAnimation.AddFrame(1);
	}
	else
	{
		for (int i = 1; i < length; i++)
		{
			increaseLengthAnimation.AddFrame(i);
		}
	}

	// peak animation is animation with time. Just show the full length explosion for the given time
	peakLengthAnimation.AddFrame(length);

	// decrease length: from length (length - 1) -> 1
	// exception: length == 1
	if (length == 1)
	{
		decreaseLengthAnimation.AddFrame(1);
	}
	else
	{
		for (int i = length - 1; i > 0; i--)
		{
			decreaseLengthAnimation.AddFrame(i);
		}
	}
}

MatPos Bomb::GetMatPosition()
{
	return matPos;
}

void Bomb::Fire(MatPos pos, int length)
{
	matPos = pos;
	this->length = length;

	exploded = false;
	peakAnimationStarted = false;
	decreaseAnimationStarted = false;

	finished = false;


	InitLengthAnimation();

	fireAnimation.Start(BombConst::SpriteSheet::Fire::TIME_FRAME_CHANGE_COUNT, false);
}

void Bomb::StartExplodeAnimation()
{
	// start the explosion texture animation
	explosionAnimation.Start(ExplosionConst::SpriteSheet::TIME_FRAME_CHANGE_COUNT, false);

	// start the length increase animation
	StartIncreaseLengthAnimation();

	exploded = true;
}

void Bomb::StartIncreaseLengthAnimation()
{
	float increaseTotalTime = ExplosionConst::TOTAL_TIME * ExplosionConst::LengthAnimation::INCREASE_TIME_PERCENT;
	increaseLengthAnimation.Start(increaseTotalTime / length, false);

	currentLengthAnimation = &increaseLengthAnimation;
}

void Bomb::StartPeakLengthAnimation()
{
	float peakTotalTime = ExplosionConst::TOTAL_TIME * ExplosionConst::LengthAnimation::PEAK_TIME_PERCENT;
	peakLengthAnimation.Start(peakTotalTime, peakTotalTime);

	currentLengthAnimation = &peakLengthAnimation;

	peakAnimationStarted = true;
}

void Bomb::StartDecreaseLengthAnimation()
{
	float decreaseTotalTime = ExplosionConst::TOTAL_TIME * ExplosionConst::LengthAnimation::DECREASE_TIME_PERCENT;
	decreaseLengthAnimation.Start(decreaseTotalTime / length, false);

	currentLengthAnimation = &decreaseLengthAnimation;

	decreaseAnimationStarted = true;
}

bool Bomb::ShouldDrawExplosion()
{
	if (!exploded)
	{
		return false;
	}

	// explosion started
	return increaseLengthAnimation.IsPlaying() || 
		peakLengthAnimation.IsPlaying() || 
		decreaseLengthAnimation.IsPlaying();
}

void Bomb::Update(float dt)
{
	if (finished)
	{
		return;
	}

	fireAnimation.Update(dt);
	explosionAnimation.Update(dt);
	increaseLengthAnimation.Update(dt);
	peakLengthAnimation.Update(dt);
	decreaseLengthAnimation.Update(dt);

	// check if the explosion animation should start
	if (fireAnimation.GetCurrentFrameIndex() == BombConst::SpriteSheet::Fire::FRAME_START_EXPLOSION && !exploded)
	{
		StartExplodeAnimation();
	}

	if (exploded)
	{
		// if the increase length animations has finished, then start the peak length animation or the decrease length animation
		if (!increaseLengthAnimation.IsPlaying())
		{
			// if the peak animation hasn't started, then start it
			if (!peakAnimationStarted)
			{
				StartPeakLengthAnimation();
			}
			else
			{
				// if the peak animation has finished and the decreaseAnimation hasn't started, then start it
				if (!peakLengthAnimation.IsPlaying() && !decreaseAnimationStarted)
				{
					StartDecreaseLengthAnimation();
				}
			}
		}
	}


	// check if the bomb has finished
	if (!fireAnimation.IsPlaying())
	{
		finished = true;
	}
}

void Bomb::Draw(sf::RenderWindow& window)
{
	if (finished)
	{
		return;
	}

	if (ShouldDrawExplosion())
	{
		int explosionIndex = explosionAnimation.GetCurrentFrame();
		int currentLength = currentLengthAnimation->GetCurrentFrame();

		DrawExplosionFrame(window, matPos, ExplosionConst::SpriteSheet::CENTER[explosionIndex]);
		if (currentLength > 0)
		{
			DrawYSide(window, true, currentLength, explosionIndex);
			DrawYSide(window, false, currentLength, explosionIndex);
			DrawXSide(window, true, currentLength, explosionIndex);
			DrawXSide(window, false, currentLength, explosionIndex);
		}
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

bool Bomb::HasEnded()
{
	return finished;
}

void Bomb::DrawYSide(sf::RenderWindow& window, bool up, int length, int explosionIndex)
{
	int sign = up ? -1 : 1;

	MatPos pos = matPos;
	pos.l += 1 * sign;

	// if it's not empty, then return. Don't draw over a wall
	if (!world->IsCellEmpty(pos))
	{
		return;
	}

	// Side
	// draw the side explosion if the next cell is empty. Otherwise the peak should be drawn
	while (length > 1 && world->IsCellEmpty(pos.l + 1 * sign, pos.c))
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

void Bomb::DrawXSide(sf::RenderWindow& window, bool right, int length, int explosionIndex)
{
	int sign = right ? 1 : -1;

	MatPos pos = matPos;
	pos.c += 1 * sign;

	// if it's not empty, then return. Don't draw over a wall
	if (!world->IsCellEmpty(pos))
	{
		return;
	}

	// Side
	// draw the side explosion if the next cell is empty. Otherwise the peak should be drawn
	while (length > 1 && world->IsCellEmpty(pos.l, pos.c + 1 * sign))
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