#ifndef _MAP_H_
#define _MAP_H_

#include <iostream>
#include "GraphicsConst.h"
#include "Grid.h"
#include "SDL.h"
#include "Camera.h"
#include <vector>

class Map {
private:
	Grid **_grid;
	int _mapWidth, _mapHeight;
	float _gridWidth, _gridHeight;
public:
	Map(const int &mapWidth, const int &mapHeight, const float &gridWidth, const float &gridHeight, const int &defaulVal);
	Map(const int &width, const int &height, const int &defaulVal);
	~Map();
	Map(const Map &obj);
	void generateWall(int wallCount, int spawnRegionOffset, int wallLenght);
	void resetMap();
	void resetStatus();
	void reinit();

	void setGridWidth(float tilesize);
	void setGridVal(const int &w,const int &h, const int &val);

	const int getGridVal(const int &w, const int &h);

	Grid* getStartGrid();
	Grid* getEndGrid();
	const int getWidth();
	const int getHeight();
	Grid* getGrid(const int &w, const int &h);

	
	Grid* getNeighbor(Grid* current,const int &direction);

	void draw(SDL_Renderer *rend);

	// Debugging methods
	void debug_printGrid();
};

#endif _MAP_H_