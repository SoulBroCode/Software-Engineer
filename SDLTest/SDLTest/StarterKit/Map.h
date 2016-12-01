#ifndef _MAP_H_
#define _MAP_H_

#include <iostream>
#include "GraphicsConst.h"
#include "Grid.h"
#include "SDL.h"
class Map {
private:
	Grid **_grid;
	int _mapWidth, _mapHeight;
	float _gridWidth, _gridHeight;
public:
	Map(int mapWidth, int mapHeight, float gridWidth, float gridHeight, int defaulVal);
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

	void draw(SDL_Renderer *rend ,int x0, int y0);

	// Debugging methods
	void debug_printGrid();
};

#endif _MAP_H_