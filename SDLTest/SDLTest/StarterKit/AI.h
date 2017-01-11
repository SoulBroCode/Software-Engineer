#ifndef _AI_H_
#define _AI_H_

#include <math.h>
#include <vector>
#include "Map.h"


class AI {
private:
	Map* mMap;
	Grid* mCurrentGrid;
	std::vector<Grid*> mPath;
	
	int mMoveTimer;
	
	char mReachPlayer;
	const int TIME_TO_MOVE = 200;

	bool mReadyToMove;
public:
	
	AI();
	AI(Map* map , short posX, short posY);
	~AI();
	
	void print()
	{
		std::cout << "AI PRINTING" << std::endl;
	}
	void update(unsigned int deltatime);


	void setPath(const std::vector<Grid*> path);
	void setCurrentGrid(short int posX, short int posY);

	short getX();
	short getY();

	char getReachPlayer();
};

#endif 