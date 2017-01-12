#include "Player.h"
Player::Player()
{
}

Player::Player(Map* map, short posX, short posY) 
{
	mMap = map;
	mCurrentGrid = new Grid(posX, posY);
	TIME_TO_MOVE = 1000;
	mMoving = false;
}
Player::~Player()
{
}



void Player::update(unsigned int deltatime)
{

	mMoveTimer -= deltatime;
	if (mMoveTimer < 0) {
		mMoveTimer = TIME_TO_MOVE;
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
			short newPosX = mCurrentGrid->getX() + dirX;
			short newPosY = mCurrentGrid->getY() + dirY;
			int value = mMap->getGridVal(newPosX, newPosY);
			if (value != GRID_WALL && value != GRID_START)
			{
				moved = true;
				mMap->setGridVal(mCurrentGrid->getX(), mCurrentGrid->getY(), GRID_FIELD);
				mCurrentGrid->setGridCoord(newPosX, newPosY);
				mMap->setGridVal(newPosX, newPosY, GRID_END);
				mMoving = true;
			}
			
		}
	}
	
}




void Player::setCurrentGrid(short int posX, short int posY)
{
	mCurrentGrid = new Grid(posX, posY);
}

short Player::getX()
{
	return mCurrentGrid->getX();
}
short Player::getY()
{
	return  mCurrentGrid->getY();
}

void Player::setMoving(bool move)
{
	mMoving = move;
}
bool Player::getMoving()
{
	return mMoving;
}