#include "AI.h"
AI::AI()
{
}

AI::AI(Map* map, short posX, short posY) :
	mMoveTimer(0),
	mReachPlayer(0),
	mReadyToMove(true)
{
	mMap = map;

	mCurrentGrid = new Grid(posX, posY);
	
}
AI::~AI()
{
}



void AI::update(unsigned int deltatime)
{
	if (mReachPlayer == 0)
	{
		mMoveTimer -= deltatime;
		if (mMoveTimer < 0) {
			mMoveTimer = TIME_TO_MOVE;
			if (!mPath.empty())
			{
				if (mPath.size() != 1)
				{
					mMap->setGridVal(mCurrentGrid->getX(), mCurrentGrid->getY(), GRID_FIELD);
					mCurrentGrid = mPath.back();
					mPath.pop_back();
					mMap->setGridVal(mCurrentGrid->getX(), mCurrentGrid->getY(), GRID_START);
				}
				else 
				{
					mMap->setGridVal(mCurrentGrid->getX(), mCurrentGrid->getY(), GRID_FIELD);
					mPath.pop_back();
					mReachPlayer = 1;
				}
			}
		}
	}
}



void AI::setPath(const std::vector<Grid*> path)
{
	mPath = path;
	if (mReadyToMove)
	{
		mReachPlayer = 0;
		mReadyToMove = false;
	}

}

void AI::setCurrentGrid(short int posX, short int posY)
{
	mCurrentGrid = new Grid(posX, posY);
}

short AI::getX()
{
	return mCurrentGrid->getX();
}
short AI::getY()
{
	return  mCurrentGrid->getY();
}

char AI::getReachPlayer()
{
	return mReachPlayer;
}