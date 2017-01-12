#ifndef _AI_H_
#define _AI_H_

#include <math.h>
#include <vector>
#include "Map.h"

class AI {
private:
	Map* mMap;
	Grid* mCurrentGrid; //position the ai is on
	std::vector<Grid*> mPath;
	
	int mMoveTimer;
	
	char mReachPlayer;
	const int TIME_TO_MOVE = 70; //delay move

	bool mReadyToMove; 

	bool mReachHalfWay; //use to check if ai reach half way to redo Astar
	int mSizeHalfway;

public:
	AI();
	AI(Map* map , short posX, short posY);
	~AI();
	
	void update(unsigned int deltatime);


	void setPath(std::vector<Grid*> path);
	void setCurrentGrid(short int posX, short int posY);

	short getX();
	short getY();

	char getReachPlayer();

	bool getReachHalfWay();
	void setReachHalfWay(bool reachHalfWay);
};

#endif 