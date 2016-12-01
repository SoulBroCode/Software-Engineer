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
	Map		  *_refMap;
	int		  _mapWidth;
	int		  _mapHeight;
	int		  _heuristicFunc;

private:
	double heuristicFunction(Grid current, Grid target);

public:
	Astar(Map *refMap);
	~Astar();

	bool findPath(Grid *start, Grid *end);
	void setHeuristicFunc(int num);
};

#endif _A_STAR_H_