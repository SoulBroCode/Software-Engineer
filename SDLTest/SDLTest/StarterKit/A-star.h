#ifndef _A_STAR_H_
#define _A_STAR_H_

#include "Map.h"
#include "GraphicsConst.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define _USE_MATH_DEFINES
#include <math.h>

class Astar {
private:
	Map*	  _refMap;
	int		  _mapWidth;
	int		  _mapHeight;
	int		  _heuristicFunc;
	Grid* _refToLastGrid;
	
private:
	void rebuildPath(std::vector<Grid*> &paths, Grid *start, Grid *end, int &loopCount);
	double heuristicFunction(Grid current, Grid target);
	std::vector<Grid*> paths;
public:
	int test;
	
	Astar(Map* _refMap);
	~Astar();
	const std::vector<Grid*>& findPath(short AIPosX, short AIPosY, short PlayerPosX, short PlayerPosY);
	bool findPath(Grid *start, Grid *end);
	void setHeuristicFunc(int num);
};

#endif _A_STAR_H_