#ifndef _AI_H_
#define _AI_H_

#include <math.h>
#include <vector>
#include "Map.h"
#include "ThreadPool.h"

class AI {
private:
	Map* _mainMap;
	Grid* _currentGrid;
	std::vector<Grid*> _path;
	
	int moveTimer;
	
	char _finishPath;
public:
	int TIME_TO_MOVE;
	AI();
	AI(Map* map, short posX, short posY);
	~AI();
	
	void ready();
	void addTask();
	void update(unsigned int deltatime);

	void setPath(const std::vector<Grid*> &path);
	void setCurrentGrid(short int posX, short int posY);

	short getX();
	short getY();
};

#endif 