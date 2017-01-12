
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <math.h>
#include <vector>
#include "Map.h"

class Player {
private:
	Map* mMap;
	Grid* mCurrentGrid;
	std::vector<Grid*> mPath;
	bool mMoving;
	int mMoveTimer;
	int TIME_TO_MOVE;
public:
	
	Player();
	Player(Map* map, short posX, short posY);
	~Player();

	void setCurrentGrid(short int posX, short int posY);
	void update(unsigned int deltatime);

	short getX();
	short getY();

	void setMoving(bool move);
	bool getMoving();
};

#endif 