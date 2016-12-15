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
			int randomDirX = rand() % 3;
			int randomDirY = rand() % 3;
			if (randomDirX == 2)
				randomDirX = -1;
			if (randomDirY == 2)
				randomDirY = -1;

			short newPosX = _currentGrid->getX() + randomDirX;
			short newPosY = _currentGrid->getY() + randomDirY;
			int value = _mainMap->getGridVal(newPosX, newPosY);
			if (value != GRID_WALL)
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