#include "Bomb.h"

Bomb::Bomb(World* world, const char* bombFireTexture, const char* bombExplosionTexture, const char* explosionBodyTexture) :
	bombFireAnimation{ BombFire::SpriteSheet::TAG },
	bombExplosionAnimation{ BombExposion::SpriteSheet::TAG },
	explosionBodyAnimation{ ExplosionConst::SpriteSheet::TAG },
	increaseLengthAnimation{ ExplosionConst::LengthAnimation::TAG },
	decreaseLengthAnimation{ ExplosionConst::LengthAnimation::TAG },
	peakLengthAnimation{ ExplosionConst::LengthAnimation::TAG }
{
	if (!this->bombFireTexture.loadFromFile(bombFireTexture))
	{
		cout << "error loading bombFireTexture";
		exit(-1);
	}

	if (!this->bombExplosionTexture.loadFromFile(bombExplosionTexture))
	{
		cout << "error loading bombExplosionTexture";
		exit(-1);
	}

	if (!this->explosionBodyTexture.loadFromFile(explosionBodyTexture))
	{
		cout << "error loading explosionBodyTexture";
		exit(-1);
	}

	this->world = world;

	InitBombFireAnimation();
	InitBombExplosionAnimation();
	InitExplosionBodyAnimation();
}

Bomb::~Bomb()
{
}

void Bomb::InitBombFireAnimation()
{
	using namespace BombFire::SpriteSheet;

	for (int i = 0; i < COUNT; i++)
	{
		bombFireAnimation.AddFrame(
			sf::IntRect(
				FRAMES[i].c * FRAME_WIDTH,
				FRAMES[i].l * FRAME_HEIGHT,
				FRAME_WIDTH,
				FRAME_HEIGHT
			)
		);
	}
}

void Bomb::InitBombExplosionAnimation()
{
	using namespace BombExposion::SpriteSheet;

	for (int i = 0; i < COUNT; i++)
	{
		bombExplosionAnimation.AddFrame(
			sf::IntRect(
				FRAMES[i].c * FRAME_WIDTH,
				FRAMES[i].l * FRAME_HEIGHT,
				FRAME_WIDTH,
				FRAME_HEIGHT
			)
		);
	}
}

void Bomb::InitExplosionBodyAnimation()
{
	// animation just with the indexes from the array with frames positions in the sprite sheet
	for (int i = 0; i < ExplosionConst::SpriteSheet::COUNT; i++)
	{
		explosionBodyAnimation.AddFrame(i);
	}
}

void Bomb::InitLengthAnimation()
{
	// increase lenght: from lenght 1 -> (lenght - 1)
	// exception: lenght == 1
	if (lenght == 1)
	{
		increaseLengthAnimation.AddFrame(1);
	}
	else
	{
		for (int i = 1; i < lenght; i++)
		{
			increaseLengthAnimation.AddFrame(i);
		}
	}

	// peak animation is animation with time. Just show the full lenght explosion for the given time
	peakLengthAnimation.AddFrame(lenght);

	// decrease lenght: from lenght (lenght - 1) -> 1
	// exception: lenght == 1
	if (lenght == 1)
	{
		decreaseLengthAnimation.AddFrame(1);
	}
	else
	{
		for (int i = lenght - 1; i > 0; i--)
		{
			decreaseLengthAnimation.AddFrame(i);
		}
	}
}

MatPos Bomb::GetMatPosition()
{
	return matPos;
}

bool Bomb::HasEnded()
{
	return finished;
}

void Bomb::Fire(MatPos pos, int lenght)
{
	matPos = pos;
	this->lenght = lenght;

	exploded = false;
	peakAnimationStarted = false;
	decreaseAnimationStarted = false;

	finished = false;


	InitLengthAnimation();
	currentLengthAnimation = &increaseLengthAnimation;

	bombFireAnimation.Start(BombFire::SpriteSheet::TIME_FRAME_CHANGE_COUNT, false);
	bombSprite.setTexture(bombFireTexture);
}

void Bomb::StartExplodeAnimation()
{
	// start the bomb explosion animation
	bombExplosionAnimation.Start(BombExposion::SpriteSheet::TIME_FRAME_CHANGE_COUNT, false);
	bombSprite.setTexture(bombExplosionTexture);

	// start the explosion body texture animation
	explosionBodyAnimation.Start(ExplosionConst::SpriteSheet::TIME_FRAME_CHANGE_COUNT, false);

	// start the lenght increase animation
	StartIncreaseLengthAnimation();

	exploded = true;
}

void Bomb::StartIncreaseLengthAnimation()
{
	float increaseTotalTime = ExplosionConst::TOTAL_TIME * ExplosionConst::LengthAnimation::INCREASE_TIME_PERCENT;
	increaseLengthAnimation.Start(increaseTotalTime / lenght, false);

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
	decreaseLengthAnimation.Start(decreaseTotalTime / lenght, false);

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

void Bomb::RemoveBoxesInMap()
{
	for (MatPos box : boxesToRemove)
	{
		world->RemoveBox(box);
	}
	boxesToRemove.clear();
}

void Bomb::ManageLengthAnimations()
{
	if (!exploded)
	{
		return;
	}

	// if the increase lenght animations has finished, then start the peak lenght animation or the decrease lenght animation
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

void Bomb::UpdateMapMark()
{
	if (!exploded)
	{
		// the bomb is yet to explode
		if (!dangerMarkAdded)
		{
			MarkExplosionDangerInMap(lenght);
			dangerMarkAdded = true;
		}
		return;
	}


	// if increase length animation is playing or peak length animation is playing, then mark explosion in map
	if (increaseLengthAnimation.IsPlaying() || peakLengthAnimation.IsPlaying())
	{
		int currentLength = currentLengthAnimation->GetCurrentFrame();
		MarkExplosionInMap(currentLength);
		return;
	}

	// if decrease length animation is playing, then mark explosion accordingly 
	if (decreaseLengthAnimation.IsPlaying())
	{
		RemoveExplosionInMap(lenght);

		int currentLength = currentLengthAnimation->GetCurrentFrame();
		MarkExplosionInMap(currentLength);
	}
	else
	{
		// the decrease length animation has eneded => remove the marks in map & remove the boxes
		if (!explosionMarkRemoved)
		{
			RemoveExplosionInMap(lenght);
			RemoveBoxesInMap();
			explosionMarkRemoved = true;
		}
	}
}

void Bomb::Update(float dt)
{
	if (finished)
	{
		return;
	}

	bombFireAnimation.Update(dt);
	bombExplosionAnimation.Update(dt);
	explosionBodyAnimation.Update(dt);

	increaseLengthAnimation.Update(dt);
	peakLengthAnimation.Update(dt);
	decreaseLengthAnimation.Update(dt);

	// check if the explosion animation should start
	if (!bombFireAnimation.IsPlaying() && !exploded)
	{
		StartExplodeAnimation();
	}

	ManageLengthAnimations();

	UpdateMapMark();

	// check if the bomb has finished
	if (!bombFireAnimation.IsPlaying() && !bombExplosionAnimation.IsPlaying())
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
		int explosionIndex = explosionBodyAnimation.GetCurrentFrame();
		int currentLength = currentLengthAnimation->GetCurrentFrame();

		DrawExplosionFrame(window, matPos, ExplosionConst::SpriteSheet::CENTER[explosionIndex], ExplosionConst::SpriteSheet::SCALE_X);
		DrawExplosionFrame(window, matPos, ExplosionConst::SpriteSheet::CENTER[explosionIndex], ExplosionConst::SpriteSheet::SCALE_Y);
		DrawExplosionFrame(window, matPos, ExplosionConst::SpriteSheet::CENTER[explosionIndex], ExplosionConst::SpriteSheet::SCALE_CENTER);
		if (currentLength > 0)
		{
			DrawYSide(window, true, currentLength, explosionIndex);
			DrawYSide(window, false, currentLength, explosionIndex);
			DrawXSide(window, true, currentLength, explosionIndex);
			DrawXSide(window, false, currentLength, explosionIndex);
		}
	}

	DrawBomb(window);
}

void Bomb::DrawBomb(sf::RenderWindow& window)
{
	sf::IntRect currentFrame;
	sf::Vector2f scale;
	sf::Vector2f offset;

	if (!exploded)
	{
		currentFrame = bombFireAnimation.GetCurrentFrame();
		scale = BombFire::SpriteSheet::SCALE;
		offset = BombFire::SpriteSheet::OFFSET;
	}
	else
	{
		currentFrame = bombExplosionAnimation.GetCurrentFrame();
		scale = BombExposion::SpriteSheet::SCALE;
		offset = BombExposion::SpriteSheet::OFFSET;

		if (bombExplosionAnimation.GetCurrentFrameIndex() >= BombExposion::SpriteSheet::FRAME_BEGIN_SMOKE)
		{
			bombSprite.setColor(sf::Color(255, 255, 255, BombExposion::SpriteSheet::SMOKE_ALPHA));
		}
	}

	bombSprite.setOrigin(
		currentFrame.width / 2,
		currentFrame.height / 2
	);

	bombSprite.setScale(
		WorldConst::CELL_WIDTH / currentFrame.width * scale.x,
		WorldConst::CELL_HEIGHT / currentFrame.height * scale.y
	);

	bombSprite.setPosition(
		matPos.c  * WorldConst::CELL_WIDTH + WorldConst::CELL_WIDTH / 2 + BombFire::SpriteSheet::OFFSET.x,
		matPos.l * WorldConst::CELL_HEIGHT + WorldConst::CELL_HEIGHT / 2 + BombFire::SpriteSheet::OFFSET.y
	);

	bombSprite.setTextureRect(currentFrame);
	window.draw(bombSprite);
}

void Bomb::DrawSpriteAt(sf::RenderWindow& window, sf::Sprite& sprite, MatPos pos, sf::Vector2f scale)
{
	sprite.setOrigin(
		ExplosionConst::SpriteSheet::FRAME_WIDTH / 2,
		ExplosionConst::SpriteSheet::FRAME_HEIGHT / 2
	);

	sprite.setScale(
		WorldConst::CELL_WIDTH / ExplosionConst::SpriteSheet::FRAME_WIDTH * scale.x,
		WorldConst::CELL_HEIGHT / ExplosionConst::SpriteSheet::FRAME_HEIGHT * scale.y
	);

	sprite.setPosition(
		pos.c  * WorldConst::CELL_WIDTH + WorldConst::CELL_WIDTH / 2,
		pos.l * WorldConst::CELL_HEIGHT + WorldConst::CELL_HEIGHT / 2
	);

	window.draw(sprite);
}

void Bomb::DrawExplosionFrame(sf::RenderWindow& window, MatPos pos, MatPos sheetPos, sf::Vector2f scale)
{
	sf::Sprite sprite(
		explosionBodyTexture,
		sf::IntRect(
			sheetPos.c * ExplosionConst::SpriteSheet::FRAME_WIDTH,
			sheetPos.l * ExplosionConst::SpriteSheet::FRAME_HEIGHT,
			ExplosionConst::SpriteSheet::FRAME_WIDTH,
			ExplosionConst::SpriteSheet::FRAME_HEIGHT
		)
	);

	DrawSpriteAt(window, sprite, pos, scale);
}

void Bomb::DrawYPeak(sf::RenderWindow& window, bool up, MatPos pos, int explosionIndex)
{
	if (up) {
		DrawExplosionFrame(window, pos, ExplosionConst::SpriteSheet::PEAK_UP[explosionIndex], ExplosionConst::SpriteSheet::SCALE_X);
	}
	else
	{
		DrawExplosionFrame(window, pos, ExplosionConst::SpriteSheet::PEAK_DOWN[explosionIndex], ExplosionConst::SpriteSheet::SCALE_X);
	}

	return;
}

void Bomb::DrawXPeak(sf::RenderWindow& window, bool right, MatPos pos, int explosionIndex)
{
	if (right) {
		DrawExplosionFrame(window, pos, ExplosionConst::SpriteSheet::PEAK_RIGHT[explosionIndex], ExplosionConst::SpriteSheet::SCALE_Y);
	}
	else
	{
		DrawExplosionFrame(window, pos, ExplosionConst::SpriteSheet::PEAK_LEFT[explosionIndex], ExplosionConst::SpriteSheet::SCALE_Y);
	}

	return;
}

void Bomb::DrawYSide(sf::RenderWindow& window, bool up, int lenght, int explosionIndex)
{
	int sign = up ? -1 : 1;

	MatPos pos = matPos;
	pos.l += 1 * sign;

	// if it's not empty, then return. Don't draw over a wall
	if (world->IsCellWall(pos))
	{
		return;
	}

	if (world->IsCellBox(pos))
	{
		DrawYPeak(window, up, pos, explosionIndex);
		return;
	}

	// Side
	// draw the side explosion if the next cell is empty. Otherwise the peak should be drawn
	while (lenght > 1)
	{
		if (world->IsCellWall(pos.l + 1 * sign, pos.c))
		{
			break;
		}

		DrawExplosionFrame(window, pos, ExplosionConst::SpriteSheet::SIDE_Y[explosionIndex], ExplosionConst::SpriteSheet::SCALE_X);

		lenght--;
		pos.l += 1 * sign;

		if (world->IsCellBox(pos.l, pos.c))
		{
			break;
		}
	}

	DrawYPeak(window, up, pos, explosionIndex);
}

void Bomb::DrawXSide(sf::RenderWindow& window, bool right, int lenght, int explosionIndex)
{
	int sign = right ? 1 : -1;

	MatPos pos = matPos;
	pos.c += 1 * sign;

	// if it's not empty, then return. Don't draw over a wall
	if (world->IsCellWall(pos))
	{
		return;
	}

	if (world->IsCellBox(pos))
	{
		DrawXPeak(window, right, pos, explosionIndex);
		return;
	}

	// Side
	// draw the side explosion if the next cell is empty. Otherwise the peak should be drawn
	while (lenght > 1)
	{
		if (world->IsCellWall(pos.l, pos.c + 1 * sign))
		{
			break;
		}

		DrawExplosionFrame(window, pos, ExplosionConst::SpriteSheet::SIDE_X[explosionIndex], ExplosionConst::SpriteSheet::SCALE_Y);

		lenght--;
		pos.c += 1 * sign;

		if (world->IsCellBox(pos.l, pos.c))
		{
			break;
		}
	}

	DrawXPeak(window, right, pos, explosionIndex);
}

void Bomb::MarkExplosionXSideInMap(int lenght, bool right, char ch)
{
	int sign = right ? 1 : -1;
	MatPos pos = matPos;

	while (lenght >= 0)
	{
		if (world->IsCellWall(pos))
		{
			return;
		}

		if (world->IsCellBox(pos))
		{
			if (ch == WorldConst::EXPLOSION)
			{
				boxesToRemove.insert(pos);
			}
			return;
		}

		world->MarkExplosionBody(pos, ch);

		pos.l += 1 * sign;
		lenght--;
	}
}

void Bomb::MarkExplosionYSideInMap(int lenght, bool up, char ch)
{
	int sign = up ? -1 : 1;
	MatPos pos = matPos;

	while (lenght >= 0)
	{
		if (world->IsCellWall(pos))
		{
			return;
		}

		if (world->IsCellBox(pos))
		{
			if (ch == WorldConst::EXPLOSION)
			{
				boxesToRemove.insert(pos);
			}
			return;
		}

		world->MarkExplosionBody(pos, ch);
		
		pos.c += 1 * sign;
		lenght--;
	}
}

void Bomb::MarkExplosionInMap(int lenght)
{
	MarkExplosionXSideInMap(lenght, true, WorldConst::EXPLOSION);
	MarkExplosionXSideInMap(lenght, false, WorldConst::EXPLOSION);
	MarkExplosionYSideInMap(lenght, true, WorldConst::EXPLOSION);
	MarkExplosionYSideInMap(lenght, false, WorldConst::EXPLOSION);
}

void Bomb::MarkExplosionDangerInMap(int lenght)
{
	MarkExplosionXSideInMap(lenght, true, WorldConst::EXPLOSION_DANGER);
	MarkExplosionXSideInMap(lenght, false, WorldConst::EXPLOSION_DANGER);
	MarkExplosionYSideInMap(lenght, true, WorldConst::EXPLOSION_DANGER);
	MarkExplosionYSideInMap(lenght, false, WorldConst::EXPLOSION_DANGER);
}

void Bomb::RemoveExplosionInMap(int lenght)
{
	MarkExplosionXSideInMap(lenght, true, WorldConst::FLOOR);
	MarkExplosionXSideInMap(lenght, false, WorldConst::FLOOR);
	MarkExplosionYSideInMap(lenght, true, WorldConst::FLOOR);
	MarkExplosionYSideInMap(lenght, false, WorldConst::FLOOR);
}