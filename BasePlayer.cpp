#include "BasePlayer.h"

using namespace PlayerConst;

BasePlayer::BasePlayer(World* world, SurprisesManager* surpriseManager, const char* texture, MatPos pos, string name) :
	downAnimation{ SpriteSheet::Move::TAG },
	upAnimation{ SpriteSheet::Move::TAG },
	rightAnimation{ SpriteSheet::Move::TAG },
	leftAnimation{ SpriteSheet::Move::TAG },
	stayAnimation{ SpriteSheet::Stay::TAG },
	deadAnimation{ SpriteSheet::Dead::TAG },
	lifeLostAnimation{ SpriteSheet::LifeLost::TAG }
{
	if (!spriteSheetTexture.loadFromFile(texture))
	{
		cout << "error loading player spriteSheetTexture";
		exit(-1);
	}

	InitSprite();
	InitAnimations();

	this->world = world;
	this->name = name;
	this->surpriseManager = surpriseManager;

	this->lifesCount = LIFES_COUNT;

	position.x = pos.c * WorldConst::CELL_WIDTH;
	position.y = pos.l * WorldConst::CELL_HEIGHT;

	desirePosition = position;

	isMoving = false;
	isStaying = false;
	isDying = false;
	isDead = false;
	isInvincible = false;

	direction = Direction::DOWN;

	Stay();
}

void BasePlayer::InitSprite()
{
	sprite.setTexture(spriteSheetTexture);
	sprite.setTextureRect(
		sf::IntRect(
			SpriteSheet::DEFAULT_FRAME.c * SpriteSheet::FRAME_WIDTH,
			SpriteSheet::DEFAULT_FRAME.l * SpriteSheet::FRAME_HEIGHT,
			SpriteSheet::FRAME_WIDTH,
			SpriteSheet::FRAME_HEIGHT
		)
	);
	sprite.setScale(
		WorldConst::CELL_WIDTH / SpriteSheet::FRAME_WIDTH,
		WorldConst::CELL_HEIGHT / SpriteSheet::FRAME_HEIGHT
	);
}

void BasePlayer::InitAnimations()
{
	InitAnimation(rightAnimation, SpriteSheet::Move::Right::COUNT, SpriteSheet::Move::Right::LINE);
	InitAnimation(upAnimation, SpriteSheet::Move::Up::COUNT, SpriteSheet::Move::Up::LINE);
	InitAnimation(downAnimation, SpriteSheet::Move::Down::COUNT, SpriteSheet::Move::Down::LINE);
	InitAnimation(leftAnimation, SpriteSheet::Move::Left::COUNT, SpriteSheet::Move::Left::LINE);
	InitAnimation(deadAnimation, SpriteSheet::Dead::COUNT, SpriteSheet::Dead::LINE);

	InitAnimation(stayAnimation, SpriteSheet::Stay::COUNT, SpriteSheet::Stay::FRAMES);
	InitAnimation(lifeLostAnimation, SpriteSheet::LifeLost::COUNT, SpriteSheet::LifeLost::LINE, SpriteSheet::LifeLost::FRAMES);

	/*InitTurnAnimation(
		turnLeftAnimation,
		SpriteSheet::Move::Down::DEFAULT_FRAME,
		SpriteSheet::Move::Down::LINE,
		SpriteSheet::Move::Left::DEFAULT_FRAME,
		SpriteSheet::Move::Left::LINE
	);
	InitTurnAnimation(
		turnRightAnimation,
		SpriteSheet::Move::Down::DEFAULT_FRAME,
		SpriteSheet::Move::Down::LINE,
		SpriteSheet::Move::Right::DEFAULT_FRAME,
		SpriteSheet::Move::Right::LINE
	);
	InitTurnAnimation(
		turnUpAnimation,
		SpriteSheet::Move::Right::DEFAULT_FRAME,
		SpriteSheet::Move::Right::LINE,
		SpriteSheet::Move::Up::DEFAULT_FRAME,
		SpriteSheet::Move::Up::LINE
	);
	InitTurnAnimation(
		turnDownAnimation,
		SpriteSheet::Move::Right::DEFAULT_FRAME,
		SpriteSheet::Move::Right::LINE,
		SpriteSheet::Move::Down::DEFAULT_FRAME,
		SpriteSheet::Move::Down::LINE
	);*/
}

void BasePlayer::InitAnimation(Animation<sf::IntRect>& animation, int count, int l)
{
	for (int i = 0; i < count; i++)
	{
		animation.AddFrame(
			sf::IntRect(
				i * SpriteSheet::FRAME_WIDTH,
				l * SpriteSheet::FRAME_HEIGHT,
				SpriteSheet::FRAME_WIDTH,
				SpriteSheet::FRAME_HEIGHT
			)
		);
	}
}

void BasePlayer::InitAnimation(Animation<sf::IntRect>& animation, const int count, const int l, const int frames[])
{
	for (int i = 0; i < count; i++)
	{
		animation.AddFrame(
			sf::IntRect(
				frames[i] * SpriteSheet::FRAME_WIDTH,
				l * SpriteSheet::FRAME_HEIGHT,
				SpriteSheet::FRAME_WIDTH,
				SpriteSheet::FRAME_HEIGHT
			)
		);
	}
}

void BasePlayer::InitAnimation(Animation<sf::IntRect>& animation, const int count, const MatPos frames[])
{
	for (int i = 0; i < count; i++)
	{
		animation.AddFrame(
			sf::IntRect(
				frames[i].c * SpriteSheet::FRAME_WIDTH,
				frames[i].l * SpriteSheet::FRAME_HEIGHT,
				SpriteSheet::FRAME_WIDTH,
				SpriteSheet::FRAME_HEIGHT
			)
		);
	}
}

void BasePlayer::InitTurnAnimation(
	Animation<sf::IntRect>& animation,
	int defaultFirstPosC,
	int defaultFirstPosL,
	int defaultSecondPosC,
	int defaultSecondPosL
)
{
	animation.AddFrame(
		sf::IntRect(
			defaultFirstPosC * SpriteSheet::FRAME_WIDTH,
			defaultFirstPosL * SpriteSheet::FRAME_HEIGHT,
			SpriteSheet::FRAME_WIDTH,
			SpriteSheet::FRAME_HEIGHT
		)
	);
	animation.AddFrame(
		sf::IntRect(
			defaultSecondPosC * SpriteSheet::FRAME_WIDTH,
			defaultSecondPosL * SpriteSheet::FRAME_HEIGHT,
			SpriteSheet::FRAME_WIDTH,
			SpriteSheet::FRAME_HEIGHT
		)
	);
}

void BasePlayer::ChangeAnimation(Animation<sf::IntRect>& animation, float changeFrameTime, bool loop)
{
	if (this->animation == &animation && this->animation->IsPlaying())
	{
		return;
	}

	prevAnimation = this->animation;

	this->animation = &animation;
	this->animation->Start(changeFrameTime, loop);
}

MatPos BasePlayer::GetMatPlayerPosition()
{
	MatPos playerPos;

	playerPos.l = position.y / WorldConst::CELL_HEIGHT;
	playerPos.c = position.x / WorldConst::CELL_WIDTH;

	return playerPos;
}

bool BasePlayer::GotARandomSurprise(MatPos pos)
{
	return surpriseManager->IsCellRandomSurprise(pos);
}

bool BasePlayer::GotARandomSurprise(sf::Vector2f pos)
{
	return surpriseManager->IsCellRandomSurprise(pos);
}

bool BasePlayer::GotABombsSupplySurprise(MatPos pos)
{
	return surpriseManager->IsCellBombsSupplySurprise(pos);
}

bool BasePlayer::GotABombsSupplySurprise(sf::Vector2f pos)
{
	return surpriseManager->IsCellBombsSupplySurprise(pos);
}

bool BasePlayer::IsInGoodMatPosition()
{
	MatPos matPos = GetMatPlayerPosition();

	sf::Vector2f myPosition(matPos.c * WorldConst::CELL_WIDTH, matPos.l * WorldConst::CELL_HEIGHT);

	return myPosition == position;
}

bool BasePlayer::WillCollide(sf::Vector2f desirePosition)
{
	return world->IsCellBox(desirePosition) || world->IsCellWall(desirePosition);
}

bool BasePlayer::ReachedDesirePostion()
{
	return position == desirePosition;
}

bool BasePlayer::CanMove()
{
	if (lifeLostAnimation.IsPlaying() || IsKilled())
	{
		return false;
	}

	return true;
}

bool BasePlayer::IsKilled()
{
	return isDead || isDying;
}

bool BasePlayer::IsSurrounded()
{
	sf::Vector2f result;

	result.x = position.x + WorldConst::CELL_WIDTH;
	result.y = position.y;
	if (!WillCollide(result))
	{
		return false;
	}

	result.x = position.x - WorldConst::CELL_WIDTH;
	result.y = position.y;
	if (!WillCollide(result))
	{
		return false;
	}

	result.x = position.x;
	result.y = position.y + WorldConst::CELL_HEIGHT;
	if (!WillCollide(result))
	{
		return false;
	}

	result.x = position.x;
	result.y = position.y - WorldConst::CELL_HEIGHT;
	if (!WillCollide(result))
	{
		return false;
	}

	return true;
}

sf::Vector2f BasePlayer::GetDesiredPosition(Direction dir)
{
	MatPos matPos = GetMatPlayerPosition();
	bool isInGoodPosition = IsInGoodMatPosition();

	sf::Vector2f result = position;

	switch (dir)
	{
	case Direction::RIGHT:
		result.x = (matPos.c + 1) * WorldConst::CELL_WIDTH;
		break;

	case Direction::LEFT:
		if (isInGoodPosition)
		{
			result.x = (matPos.c - 1) * WorldConst::CELL_WIDTH;
		}
		else
		{
			result.x = matPos.c * WorldConst::CELL_WIDTH;
		}
		break;

	case Direction::DOWN:
		result.y = (matPos.l + 1) * WorldConst::CELL_HEIGHT;
		break;

	case Direction::UP:
		if (isInGoodPosition)
		{
			result.y = (matPos.l - 1) * WorldConst::CELL_HEIGHT;
		}
		else
		{
			result.y = matPos.l * WorldConst::CELL_HEIGHT;
		}
		break;
	}

	return result;
}

void BasePlayer::MoveUp()
{
	if (!CanMove())
	{
		return;
	}

	// don t change the position if the player isn t in the desire position
	if (!IsInGoodMatPosition())
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::DOWN || direction == Direction::UP)
		{
			sf::Vector2f newDesiredPosition = GetDesiredPosition(Direction::UP);
			if (WillCollide(newDesiredPosition))
			{
				// collision => player won't move
				return;
			}

			desirePosition = newDesiredPosition;
			direction = Direction::UP;
			ChangeAnimation(upAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
			isMoving = true;
			isStaying = false;
		}
		return;
	}

	sf::Vector2f newDesiredPosition = GetDesiredPosition(Direction::UP);
	if (WillCollide(newDesiredPosition))
	{
		// collision => player won't move
		return;
	}

	desirePosition = newDesiredPosition;
	direction = Direction::UP;
	ChangeAnimation(upAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
	isMoving = true;
	isStaying = false;
}

void BasePlayer::MoveDown()
{
	if (!CanMove())
	{
		return;
	}

	// don t change the position if the player isn t in the desire position
	if (!IsInGoodMatPosition())
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::UP || direction == Direction::DOWN)
		{
			sf::Vector2f newDesiredPosition = GetDesiredPosition(Direction::DOWN);
			if (WillCollide(newDesiredPosition))
			{
				// collision => player won't move
				return;
			}

			desirePosition = newDesiredPosition;
			direction = Direction::DOWN;
			ChangeAnimation(downAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
			isMoving = true;
			isStaying = false;
		}
		return;
	}

	sf::Vector2f newDesiredPosition = GetDesiredPosition(Direction::DOWN);
	if (WillCollide(newDesiredPosition))
	{
		// collision => player won't move
		return;
	}

	desirePosition = newDesiredPosition;
	direction = Direction::DOWN;
	ChangeAnimation(downAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
	isMoving = true;
	isStaying = false;
}

void BasePlayer::MoveLeft()
{
	if (!CanMove())
	{
		return;
	}

	// don t change the position if the player isn t in the desire position
	if (!IsInGoodMatPosition())
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::RIGHT || direction == Direction::LEFT)
		{
			sf::Vector2f newDesiredPosition = GetDesiredPosition(Direction::LEFT);
			if (WillCollide(newDesiredPosition))
			{
				// collision => player won't move
				return;
			}

			desirePosition = newDesiredPosition;
			direction = Direction::LEFT;
			ChangeAnimation(leftAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
			isMoving = true;
			isStaying = false;
		}
		return;
	}

	sf::Vector2f newDesiredPosition = GetDesiredPosition(Direction::LEFT);
	if (WillCollide(newDesiredPosition))
	{
		// collision => player won't move
		return;
	}

	desirePosition = newDesiredPosition;
	direction = Direction::LEFT;
	ChangeAnimation(leftAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
	isMoving = true;
	isStaying = false;
}

void BasePlayer::MoveRight()
{
	if (!CanMove())
	{
		return;
	}

	// don t change the position if the player isn t in the desire position
	if (!IsInGoodMatPosition())
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::LEFT || direction == Direction::RIGHT)
		{
			sf::Vector2f newDesiredPosition = GetDesiredPosition(Direction::RIGHT);
			if (WillCollide(newDesiredPosition))
			{
				// collision => player won't move
				return;
			}

			desirePosition = newDesiredPosition;
			direction = Direction::RIGHT;
			ChangeAnimation(rightAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
			isMoving = true;
			isStaying = false;
		}
		return;
	}

	sf::Vector2f newDesiredPosition = GetDesiredPosition(Direction::RIGHT);
	if (WillCollide(newDesiredPosition))
	{
		// collision => player won't move
		return;
	}

	desirePosition = newDesiredPosition;
	direction = Direction::RIGHT;
	ChangeAnimation(rightAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
	isMoving = true;
	isStaying = false;
}

void BasePlayer::Move(Direction dir)
{
	switch (dir)
	{
	case Direction::RIGHT:
		MoveRight();
		return;

	case Direction::LEFT:
		MoveLeft();
		return;

	case Direction::DOWN:
		MoveDown();
		return;

	case Direction::UP:
		MoveUp();
		return;
	}
}

void BasePlayer::MoveToClosestGoodMatPosition()
{
	MatPos matPos = GetMatPlayerPosition();

	// is wrong X position?
	if (matPos.c * WorldConst::CELL_WIDTH != position.x)
	{
		float xLeft = matPos.c * WorldConst::CELL_WIDTH;
		float xRight = (matPos.c + 1) * WorldConst::CELL_WIDTH;

		if (position.x - xLeft < xRight - position.x)
		{
			// left is closest
			MoveLeft();
		}
		else
		{
			// right is closest
			MoveRight();
		}
	}
	else
	{
		// Y position is wrong
		float yUp = matPos.l * WorldConst::CELL_HEIGHT;
		float yDown = (matPos.l + 1) * WorldConst::CELL_HEIGHT;

		if (position.y - yUp < yDown - position.y)
		{
			// up is closest
			MoveUp();
		}
		else
		{
			// down is closest
			MoveDown();
		}
	}
}

void BasePlayer::Stay()
{
	if (IsKilled())
	{
		return;
	}

	// stay forever
	ChangeAnimation(stayAnimation, SpriteSheet::Stay::TIME_FRAME_CHANGE_COUNT);

	isStaying = true;
	isMoving = false;
}

void BasePlayer::OnLifeLost()
{
	lifesCount--;
	if (lifesCount == 0)
	{
		OnDeath();
		return;
	}

	isMoving = false;
	isStaying = false;
	isInvincible = true;
	invincibleTimeCounter = 0;
	sprite.setColor(INVINCIBLE_COLOR);

	ChangeAnimation(lifeLostAnimation, SpriteSheet::LifeLost::TIME_FRAME_CHANGE_COUNT, false);
}

void BasePlayer::OnDeath()
{
	isMoving = false;
	isStaying = false;
	isDying = true;
	cout << name << " is dead";
	ChangeAnimation(deadAnimation, SpriteSheet::Dead::TIME_FRAME_CHANGE_COUNT, false);
}

void BasePlayer::HitBox(float dt)
{
	if (world->IsCellMarkedAsExplosion(position) && !isInvincible  && !IsKilled())
	{
		OnLifeLost();
	}

	if (isInvincible)
	{
		invincibleTimeCounter += dt;

		if (invincibleTimeCounter >= INVINCIBLE_TIME_AFTER_HIT && !world->IsCellMarkedAsExplosion(position))
		{
			isInvincible = false;
			sprite.setColor(sf::Color::White);
		}
	}	
}

void BasePlayer::CheckForSurprise()
{
	if (!surpriseManager->IsCellASurprise(position))
	{
		return;
	}
	
	SurpriseType surprise = surpriseManager->GetSurprise(position);

	surpriseManager->RemoveSurpriseFromMap(position);
	
	BoostAbilities(surprise);
}

void BasePlayer::BoostAbilities(SurpriseType surprise)
{
	switch (surprise)
	{
	case SurpriseType::RANDOM:
		cout << "random " << endl;
		break;

	case SurpriseType::BOMBS_SUPPLY:
		cout << "bombs supply" << endl;
		break;
	}
}

void BasePlayer::UpdateMovement(float dt)
{
	if (isMoving == true)
	{
		switch (direction)
		{
		case Direction::RIGHT:
			position.x += SPEED * dt;
			if (position.x >= desirePosition.x)
			{
				position.x = desirePosition.x;
				isMoving = false;
			}
			break;

		case Direction::LEFT:
			position.x -= SPEED * dt;
			if (position.x <= desirePosition.x)
			{
				position.x = desirePosition.x;
				isMoving = false;
			}
			break;

		case Direction::DOWN:
			position.y += SPEED * dt;
			if (position.y >= desirePosition.y)
			{
				position.y = desirePosition.y;
				isMoving = false;
			}
			break;

		case Direction::UP:
			position.y -= SPEED * dt;
			if (position.y <= desirePosition.y)
			{
				position.y = desirePosition.y;
				isMoving = false;
			}
			break;
		}
	}
	else if (animation->Is(SpriteSheet::Move::TAG))
	{
		Stay();
	}
}

void BasePlayer::Update(float dt)
{
	if (isDead)
	{
		return;
	}

	if (isDying && !deadAnimation.IsPlaying())
	{
		isDead = true;
		return;
	}

	if (animation->Is(SpriteSheet::LifeLost::TAG) && !animation->IsPlaying())
	{
		// life lost animation has ended
		if (IsInGoodMatPosition())
		{
			Stay();
		}
		else
		{
			// move in order to reach a good position
			Move(direction);
		}
	}

	animation->Update(dt);
	HitBox(dt);

	CheckForSurprise();

	UpdateMovement(dt);
}

void BasePlayer::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position + sf::Vector2f(0, -WorldConst::BASE_GROUND));
	sprite.setTextureRect(animation->GetCurrentFrame());
	window.draw(sprite);
}