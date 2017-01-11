#ifndef _ASTAR_H_
#define _ASTAR_H_

#include "Map.h"
#include "GraphicsConst.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define _USE_MATH_DEFINES
#include <math.h>

class AStar {
private:
	int		  _heuristicFunc;
	

private:
	void rebuildPath(std::vector<Grid*> &paths, Grid *start, Grid *end, int &loopCount, Grid* _refToLastGrid);
	double heuristicFunction(Grid current, Grid target);

public:
	AStar();
	~AStar();
	//const std::vector<Grid*>& findPath(short AIPosX, short AIPosY, short PlayerPosX, short PlayerPosY);
	const std::vector<Grid*> findPath(Map &map, short AIPosX, short AIPosY, short PlayerPosX, short PlayerPosY);
	//bool findPath(Grid *start, Grid *end);
	void setHeuristicFunc(int num);

};

#endif _A_STAR_H_