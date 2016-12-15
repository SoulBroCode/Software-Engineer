
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <math.h>
#include <vector>
#include "Map.h"
#include "ThreadPool.h"

class Player {
private:
	Map* _mainMap;
	Grid* _currentGrid;
	std::vector<Grid*> _path;
	bool moving;
	int moveTimer;
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