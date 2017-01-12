#include "Player.h"
Player::Player()
{
}

Player::Player(Map* map, short posX, short posY) 
{
	_mainMap = map;
	_currentGrid = new Grid(posX, posY);
	TIME_TO_MOVE = 1000;
	moving = false;
}
Player::~Player()
{
}



void Player::update(unsigned int deltatime)
{

	moveTimer -= deltatime;
	if (moveTimer < 0) {
		moveTimer = TIME_TO_MOVE;
		bool moved = false;
		while (!moved)
		{
			int dir = rand() % 5;
			short dirX;
			short dirY;
			switch (dir)
			{
			case 0:
				dirX = 0;
				dirY = 0;
				break;
			case 1:
				dirX = 1;
				dirY = 0;
				break;
			case 2:
				dirX = 1;
				dirY = 0;
				break;
			case 3:
				dirX = 0;
				dirY = 1;
				break;
			default:
				dirX = 0;
				dirY = -1;
				break;
			}
			short newPosX = _currentGrid->getX() + dirX;
			short newPosY = _currentGrid->getY() + dirY;
			int value = _mainMap->getGridVal(newPosX, newPosY);
			if (value != GRID_WALL && value != GRID_START)
			{
				moved = true;
				_mainMap->setGridVal(_currentGrid->getX(), _currentGrid->getY(), GRID_FIELD);
				_currentGrid->setGridCoord(newPosX, newPosY);
				_mainMap->setGridVal(newPosX, newPosY, GRID_END);
				moving = true;
			}
			
		}
	}
	
}




void Player::setCurrentGrid(short int posX, short int posY)
{
	_currentGrid = new Grid(posX, posY);
}

short Player::getX()
{
	return _currentGrid->getX();
}
short Player::getY()
{
	return  _currentGrid->getY();
}

void Player::setMoving(bool move)
{
	moving = move;
}
bool Player::getMoving()
{
	return moving;
}