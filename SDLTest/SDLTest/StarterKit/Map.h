#ifndef _MAP_H_
#define _MAP_H_

#include <iostream>
#include "GraphicsConst.h"
#include "Grid.h"

class Map {
private:
	Grid **_grid;
	int _width, _height;

public:
	Map(int width, int height);
	Map(int width, int height, int defaulVal);
	~Map();

	void resetMap();
	void reinit();
	void setGridVal(int w, int h, int val);

	int getGridVal(int w, int h);
	Grid* getStartGrid();
	Grid* getEndGrid();
	int getWidth();
	int getHeight();
	Grid* getGrid(int w, int h);
	Grid* getNeighbor(Grid* current, int direction);

	void draw(int x0, int y0);

	// Debugging methods
	void debug_printGrid();
};

#endif _MAP_H_