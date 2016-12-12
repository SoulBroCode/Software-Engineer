#ifndef _AI_H_
#define _AI_H_

#include <math.h>
#include <vector>
#include "Map.h"

class AI {
private:
	Map* _map;
	Grid* _startGrid;
	std::vector<Grid*> _path;

	int timeToMove;
	
	char _finishPath;
public:
	int TICKCONST;

	AI();
	~AI();
	void init(Map* map);

	void update(unsigned int deltatime);

	void setPath(const std::vector<Grid*> &path);
	void setStartGrid(Grid* grid);
	Grid* getStartGrid();
};

#endif 