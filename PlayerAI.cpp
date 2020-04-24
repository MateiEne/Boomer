#include "PlayerAI.h"

using namespace PlayerConst;

PlayerAI::PlayerAI(World* world, BombsManager* bombsManager, const char* texture, MatPos pos, string name) :
	BombPlayer(world, bombsManager, texture, pos, name)
{
	srand(time(NULL));
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

	BasePlayer::Update(dt);
}