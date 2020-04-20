#include "Player.h"

using namespace PlayerConst;

Player::Player(World* world, BombsManager* bombsManager, const char* texture, MatPos pos, string name) :
	BombPlayer(world, bombsManager, texture, pos, name)
{
}

Player::~Player()
{
}

void Player::MoveUp()
{
	if (!CanMove())
	{
		return;
	}

	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::DOWN)
		{
			desirePosition.y -= WorldConst::CELL_HEIGHT;
			if (WillCollide(desirePosition))
			{
				desirePosition.y += WorldConst::CELL_HEIGHT;
				return;
			}

			direction = Direction::UP;
			ChangeAnimation(upAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
			move = true;
		}
		return;
	}

	desirePosition = position;
	desirePosition.y -= WorldConst::CELL_HEIGHT;
	if (WillCollide(desirePosition))
	{
		// collision => reset desirePosition => player won't move
		desirePosition = position;
		return;
	}
	
	direction = Direction::UP;
	ChangeAnimation(upAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
	move = true;
}

void Player::MoveDown()
{
	if (!CanMove())
	{
		return;
	}

	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::UP)
		{
			desirePosition.y += WorldConst::CELL_HEIGHT;
			if (WillCollide(desirePosition))
			{
				desirePosition.y -= WorldConst::CELL_HEIGHT;
				return;
			}
			direction = Direction::DOWN;
			ChangeAnimation(downAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
			move = true;
		}
		return;
	}

	desirePosition = position;
	desirePosition.y += WorldConst::CELL_HEIGHT;
	if (WillCollide(desirePosition))
	{
		// collision => reset desirePosition => player won't move
		desirePosition = position;
		return;
	}
	
	direction = Direction::DOWN;
	ChangeAnimation(downAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
	move = true;
}

void Player::MoveLeft()
{
	if (!CanMove())
	{
		return;
	}

	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::RIGHT)
		{
			desirePosition.x -= WorldConst::CELL_WIDTH;
			if (WillCollide(desirePosition))
			{
				desirePosition.x += WorldConst::CELL_WIDTH;
				return;
			}
			direction = Direction::LEFT;
			ChangeAnimation(leftAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
			move = true;
		}
		return;
	}

	desirePosition = position;
	desirePosition.x -= WorldConst::CELL_WIDTH;
	if (WillCollide(desirePosition))
	{
		// collision => reset desirePosition => player won't move
		desirePosition = position;
		return;
	}
	
	direction = Direction::LEFT;
	ChangeAnimation(leftAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
	move = true;
}

void Player::MoveRight()
{
	if (!CanMove())
	{
		return;
	}

	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		// but player can quickly change to the oposite direction
		if (direction == Direction::LEFT)
		{
			desirePosition.x += WorldConst::CELL_WIDTH;
			if (WillCollide(desirePosition))
			{
				desirePosition.x -= WorldConst::CELL_WIDTH;
				return;
			}
			direction = Direction::RIGHT;
			ChangeAnimation(rightAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
			move = true;
		}
		return;
	}

	desirePosition = position;
	desirePosition.x += WorldConst::CELL_WIDTH;
	if (WillCollide(desirePosition))
	{
		// collision => reset desirePosition => player won't move
		desirePosition = position;
		return;
	}
	
	direction = Direction::RIGHT;
	ChangeAnimation(rightAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);
	move = true;
}
