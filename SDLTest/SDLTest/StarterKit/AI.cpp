#include "AI.h"
AI::AI()
{
}

AI::AI(Map* map, short posX, short posY) :
	mMoveTimer(0),
	mReachPlayer(0),
	mReadyToMove(true),
	mReachHalfWay(false),
	mMap(map),
	mCurrentGrid(new Grid(posX, posY))
{

}
AI::~AI()
{
	delete mCurrentGrid;
}



void AI::update(unsigned int deltatime)
{
	//check if player hasn't been reach
	if (mReachPlayer == 0)
	{
		mMoveTimer -= deltatime;
		if (mMoveTimer < 0) 
		{
			if (!mPath.empty())
			{
				//getting 1 path ahead and checking if there is another AI
				short xPos = mPath[mPath.size()-1]->getX();
				short yPos = mPath[mPath.size()-1]->getY();
				char value = mMap->getGridVal(xPos, yPos);

				if (mPath.size() == 1)
				{
					//reaching final destination
					mReachPlayer = 1;
					mMap->setGridVal(mCurrentGrid->getX(), mCurrentGrid->getY(), GRID_FIELD);
					mPath.pop_back();
				}
				else if (value != GRID_START)
				{
					//moving and reset old path
					mMap->setGridVal(mCurrentGrid->getX(), mCurrentGrid->getY(), GRID_FIELD);
					mCurrentGrid = mPath.back();
					mPath.pop_back();
					mMap->setGridVal(mCurrentGrid->getX(), mCurrentGrid->getY(), GRID_START);
						
				}

				
				mMoveTimer = TIME_TO_MOVE;
				if (mSizeHalfway > mPath.size()) {
					mReachHalfWay = true;
				}
			}		
			else
			{
				if (!mReadyToMove)
				{
					mReachPlayer = 1;
				}
			}
		}
	}
}


void AI::setPath( std::vector<Grid*> path)
{
		if (mReadyToMove)
		{
			mReachPlayer = 0;
			mReadyToMove = false;
		}
		mPath = path;
		mSizeHalfway = mPath.size() / 2;
	
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

bool AI::getReachHalfWay()
{
	return mReachHalfWay;
}

void AI::setReachHalfWay(bool reachHalfWay)
{
	mReachHalfWay = reachHalfWay;
}

char AI::getReachPlayer()
{
	return mReachPlayer;
}