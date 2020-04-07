#include "Bomb.h"

Bomb::Bomb(const char* bombTexture, const char* explosionTexture, MatPos pos, int length) :
	fireAnimation{ BombConst::SpriteSheet::Fire::TAG },
	explosionAnimation{ ExplosionConst::SpriteSheet::TAG },
	increaseLengthAnimation{ "increase" },
	decreaseLengthAnimation{ "decrease" },
	peakLengthAnimation{ "peak" }
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

	matPos = pos;
	this->length = length;

	exploded = false;
	peakAnimationStarted = false;
	decreaseAnimationStarted = false;

	InitBombSprite();
	InitAnimation(
		fireAnimation, 
		BombConst::SpriteSheet::Fire::COUNT, 
		BombConst::SpriteSheet::Fire::FRAMES, 
		BombConst::SpriteSheet::FRAME_WIDTH, 
		BombConst::SpriteSheet::FRAME_HEIGHT
	);

	InitExplosionAnimation();
	InitLengthAnimation();

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


	// to play in loop
	if (fireAnimation.GetCurrentFrameIndex() == 0)
	{
		exploded = false;
		peakAnimationStarted = false;
		decreaseAnimationStarted = false;
	}
}

void Bomb::Draw(sf::RenderWindow& window)
{
	if (ShouldDrawExplosion())
	{
		cout << currentLengthAnimation->GetTag() << endl;

		int explosionIndex = explosionAnimation.GetCurrentFrame();
		int currentLength = currentLengthAnimation->GetCurrentFrame();

		DrawExplosionFrame(window, matPos, ExplosionConst::SpriteSheet::CENTER[explosionIndex]);
		if (currentLength > 0)
		{
			DrawYSide(window, true, length, explosionIndex);
			DrawYSide(window, false, length, explosionIndex);
			DrawXSide(window, true, length, explosionIndex);
			DrawXSide(window, false, length, explosionIndex);
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

void Bomb::DrawYSide(sf::RenderWindow& window, bool up, int length, int explosionIndex)
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

void Bomb::DrawXSide(sf::RenderWindow& window, bool right, int length, int explosionIndex)
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