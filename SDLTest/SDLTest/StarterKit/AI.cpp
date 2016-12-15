#include "AI.h"
AI::AI()
{
}

AI::AI(Map* map, short posX, short posY) :
	moveTimer(0),
	_finishPath(2)
{
	_mainMap = map;
	_currentGrid = new Grid(posX, posY);
	TIME_TO_MOVE = 200;
}
AI::~AI()
{
}


void AI::addTask() {
	ThreadPool *theadpool = ThreadPool::getInstance();
	theadpool->addJob(ThreadPool::action);
}
void AI::ready()
{
	if(_finishPath != 1)
		_finishPath = 0;
	
}
void AI::update(unsigned int deltatime)
{
	if (_finishPath == 0)
	{
		moveTimer -= deltatime;
		if (moveTimer < 0) {
			moveTimer = TIME_TO_MOVE;
			if (!_path.empty())
			{
				_mainMap->setGridVal(_currentGrid->getX(), _currentGrid->getY(), GRID_FIELD);
				_currentGrid = _path.back();
				_path.pop_back();
				_mainMap->setGridVal(_currentGrid->getX(), _currentGrid->getY(), GRID_START);
			}
			else {
				_mainMap->setGridVal(_currentGrid->getX(), _currentGrid->getY(), GRID_FIELD);
				_finishPath = 1;
			}
		}
	}
}



void AI::setPath(const std::vector<Grid*> &path)
{
	_path = path;
}

void AI::setCurrentGrid(short int posX, short int posY)
{
	_currentGrid = new Grid(posX, posY);
}

short AI::getX()
{
	return _currentGrid->getX();
}
short AI::getY()
{
	return  _currentGrid->getY();
}