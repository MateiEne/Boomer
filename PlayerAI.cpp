#include "PlayerAI.h"

using namespace PlayerConst;

PlayerAI::PlayerAI(World& world, const char* texture, MatPos pos) :
	downAnimation{SpriteSheet::Move::TAG},
	upAnimation{ SpriteSheet::Move::TAG },
	rightAnimation{ SpriteSheet::Move::TAG },
	leftAnimation{ SpriteSheet::Move::TAG },
	stayAnimation{ SpriteSheet::Stay::TAG }
{
	srand(time(NULL));

	if (!spriteSheetTexture.loadFromFile(texture))
	{
		cout << "error loading player spriteSheetTexture";
		exit(-1);
	}

	this->world = &world;

	position.x = pos.c * WorldConst::CELL_WIDTH;
	position.y = pos.l * WorldConst::CELL_HEIGHT;

	desirePosition = position;

	Init();

	animation = &downAnimation;
	direction = Direction::RIGHT;
}

void PlayerAI::ChangeAnimation(Animation& animation, float changeFrameTime, bool loop)
{
	if (this->animation == &animation && this->animation->IsPlaying())
	{
		return;
	}

	this->animation = &animation;
	this->animation->Start(changeFrameTime, loop);
}

void PlayerAI::PrintRouteMap(int mat[][50])
{
	for (int i = 0; i < WorldConst::NL; i++)
	{
		for (int j = 0; j < WorldConst::NC; j++)
		{
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
}

void PlayerAI::MoveRigt()
{
	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		return;
	}
	move = true;

	desirePosition = position;
	desirePosition.x += WorldConst::CELL_WIDTH;
	direction = Direction::RIGHT;
	ChangeAnimation(rightAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);

}

void PlayerAI::MoveLeft()
{
	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		return;
	}
	move = true;

	desirePosition = position;
	desirePosition.x -= WorldConst::CELL_WIDTH;
	direction = Direction::LEFT;
	ChangeAnimation(leftAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);

}

void PlayerAI::MoveDown()
{
	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		return;
	}
	move = true;

	desirePosition = position;
	desirePosition.y += WorldConst::CELL_HEIGHT;
	direction = Direction::DOWN;
	ChangeAnimation(downAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);

}

void PlayerAI::MoveUp()
{
	// don t change the position if the player isn t in the desire position
	if (!ReachedDesirePostion())
	{
		return;
	}
	move = true;

	desirePosition = position;
	desirePosition.y -= WorldConst::CELL_HEIGHT;
	direction = Direction::UP;
	ChangeAnimation(upAnimation, SpriteSheet::Move::TIME_FRAME_CHANGE_COUNT);

}

bool PlayerAI::ReachedDesirePostion()
{
	return position == desirePosition;
}

PlayerAI::~PlayerAI()
{

}

void PlayerAI::Init()
{
	InitSprite();

	InitAnimation(rightAnimation, SpriteSheet::Move::Right::COUNT, SpriteSheet::Move::Right::LINE);
	InitAnimation(upAnimation, SpriteSheet::Move::Up::COUNT, SpriteSheet::Move::Up::LINE);
	InitAnimation(downAnimation, SpriteSheet::Move::Down::COUNT, SpriteSheet::Move::Down::LINE);
	InitAnimation(leftAnimation, SpriteSheet::Move::Left::COUNT, SpriteSheet::Move::Left::LINE);
	InitAnimation(stayAnimation, SpriteSheet::Stay::COUNT, SpriteSheet::Stay::FRAMES);
}

void PlayerAI::InitSprite()
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

void PlayerAI::InitAnimation(Animation& animation, int count, int l)
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

void PlayerAI::InitAnimation(Animation& animation, const int count, const MatPos frames[])
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

list<Direction> PlayerAI::Lee(MatPos startPos, MatPos finishPos)
{
	bool viz[50][50] = { false };
	int paths[50][50] = { 0 };

	queue<MatPos> queue;

	MatPos directions[] = { MatPos(1, 0), MatPos(0, 1), MatPos(-1, 0), MatPos(0, -1) };
	MatPos parent;
	MatPos child;
	
	queue.push(startPos);

	viz[startPos.l][startPos.c] = true;
	paths[startPos.l][startPos.c] = 1;

	parent = startPos;

	while (!queue.empty())
	{
		parent = queue.front();
		queue.pop();
		
		if (parent == finishPos)
		{
			return FindPath(paths, startPos, finishPos);
		}

		for (MatPos dir : directions)
		{
			child = parent + dir;
			if (viz[child.l][child.c] == false && world->IsCellEmpty(child))
			{
				queue.push(child);
				paths[child.l][child.c] = paths[parent.l][parent.c] + 1;
				viz[child.l][child.c] = true;
			}
		}
	}

	// cannot reach finishPos, so will return an empty list
	return list<Direction>();
}

list<Direction> PlayerAI::FindPath(int paths[][50], MatPos startPos, MatPos finishPos)
{
	list<Direction> result;
	Direction dir = direction;

	vector<MatPos> matDirections{ MatPos(1, 0), MatPos(0,1), MatPos(-1, 0), MatPos(0, -1) };
	vector<Direction> oppositeDirections{ Direction::UP, Direction::LEFT, Direction::DOWN, Direction::RIGHT };
	MatPos parent = finishPos;
	MatPos child;
	
	while (parent != startPos)
	{
		for (int i = 0; i < matDirections.size(); i++)
		{
			child = matDirections[i] + parent;
			if (paths[child.l][child.c] == paths[parent.l][parent.c] - 1)
			{
				result.push_front(oppositeDirections[i]);
				parent = child;
				break;
			}
		}
	}

	return result;
}

void PlayerAI::Move(Direction dir)
{
	switch (dir)
	{
	case Direction::RIGHT:
		MoveRigt();
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

MatPos PlayerAI::GetFinishPosition()
{
	MatPos  finishPos;

	do
	{
		finishPos.l = rand() % (WorldConst::NL - 2);
		finishPos.c = rand() % (WorldConst::NC - 2);
	} while (!world->IsCellEmpty(finishPos));

	return finishPos;
}

MatPos PlayerAI::GetStartPosition()
{
	MatPos startPos;

	startPos.l = position.y / WorldConst::CELL_HEIGHT;
	startPos.c = position.x / WorldConst::CELL_WIDTH;

	return startPos;
}

void PlayerAI::ShowPath(list<Direction> list)
{
	for (Direction dir : list)
	{
		cout << dir << " ";
	}

	cout << endl;
}

bool PlayerAI::WillCollide(sf::Vector2f desirePosition)
{
	return !world->IsCellEmpty(desirePosition);
}

void PlayerAI::Stay()
{
	ChangeAnimation(stayAnimation, SpriteSheet::Stay::TIME_FRAME_CHANGE_COUNT);
	move = false;
}

bool PlayerAI::IsSurrounded()
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

void PlayerAI::Update(float dt)
{
	if (ReachedDesirePostion())
	{
		if (IsSurrounded())
		{
			Stay();
		}
		else 
		{
			if (directionPath.empty())
			{
				MatPos startPos = GetStartPosition();
				MatPos finishPos = GetFinishPosition();
				cout << startPos << endl;
				cout << finishPos << endl;
				cout << endl;
				directionPath = Lee(startPos, finishPos);
			}
			else
			{
				Move(directionPath.front());
				directionPath.pop_front();
			}
		}
	}

	animation->Update(dt);
	if (move == true)
	{
		switch (direction)
		{
		case Direction::RIGHT:
			position.x += SPEED * dt;
			if (position.x >= desirePosition.x)
			{
				position.x = desirePosition.x;
				move = false;
			}
			break;

		case Direction::LEFT:
			position.x -= SPEED * dt;
			if (position.x <= desirePosition.x)
			{
				position.x = desirePosition.x;
				move = false;
			}
			break;

		case Direction::DOWN:
			position.y += SPEED * dt;
			if (position.y >= desirePosition.y)
			{
				position.y = desirePosition.y;
				move = false;
			}
			break;

		case Direction::UP:
			position.y -= SPEED * dt;
			if (position.y <= desirePosition.y)
			{
				position.y = desirePosition.y;
				move = false;
			}
			break;
		}
	}
	else if (animation->Is(SpriteSheet::Move::TAG))
	{
		animation->Stop();
	}
}

void PlayerAI::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	sprite.setTextureRect(animation->GetCurrentFrame());
	window.draw(sprite);
}