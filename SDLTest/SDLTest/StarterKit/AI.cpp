#include "AI.h"
AI::AI() :
	timeToMove(500),
	_finishPath(0)
{
}
AI::~AI()
{
}

void AI::init(Map* map)
{
	_map = map;
}

void AI::update(unsigned int deltatime)
{
	if (_finishPath == 0)
	{
		timeToMove -= deltatime;
		if (timeToMove < 0) {
			timeToMove = TICKCONST;
			if (!_path.empty())
			{
				_map->setGridVal(_startGrid->getX(), _startGrid->getY(), GRID_FIELD);
				_startGrid = _path.back();
				_path.pop_back();
				_map->setGridVal(_startGrid->getX(), _startGrid->getY(), GRID_START);
			}
			else {
				_map->setGridVal(_startGrid->getX(), _startGrid->getY(), GRID_FIELD);
				_finishPath = 1;
			}
		}
	}
}



void AI::setPath(const std::vector<Grid*> &path)
{
	_path = path;
}

void AI::setStartGrid(Grid* grid)
{
	_startGrid = grid;
}

Grid* AI::getStartGrid()
{
	return _startGrid;
}