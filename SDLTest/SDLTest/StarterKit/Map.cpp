#include "Map.h"

Map::Map(const int &mapWidth, const int &mapHeight, const float &gridWidth, const float &gridHeight, const int &defaultVal) : 
	_mapWidth(mapWidth), 
	_mapHeight(mapHeight),
	_gridWidth(gridWidth),
	_gridHeight(gridHeight)
{

	_grid = new Grid*[_mapWidth];
	for (int i = 0; i < _mapWidth; i++)
	{
		_grid[i] = new Grid[_mapHeight];
		for (int j = 0; j < _mapHeight; j++)
		{
			_grid[i][j].setGridCoord(i, j);
			_grid[i][j].setGridVal(defaultVal);
		}
	}
	// (width, height)
}

Map::Map(const int &width, const int &height, const int &defaultVal)
{
	_mapWidth = width;
	_mapHeight = height;
	_grid = new Grid*[_mapWidth];
	for (int i = 0; i < _mapWidth; i++)
	{
		_grid[i] = new Grid[_mapHeight];
		for (int j = 0; j < _mapHeight; j++)
		{
			_grid[i][j].setGridCoord(i , j);
			_grid[i][j].setGridVal(defaultVal);
		}
	}
	// (width, height)
}

Map::~Map()
{
	for (int i = 0; i < _mapWidth; i++)
		delete[] _grid[i];
	delete[] _grid;
}

void Map::resetMap()
{
	for (int i = 0; i < _mapWidth; i++)
		for (int j = 0; j < _mapHeight; j++)
			if (_grid[i][j].getGridVal() != 0)
			{
				_grid[i][j].setStatus(0);
				if (_grid[i][j].getGridVal() == GRID_PATH)
					_grid[i][j].setGridVal(GRID_FIELD);

			}
}

void Map::reinit()
{
	for (int i = 0; i < _mapWidth; i++)
		for (int j = 0; j < _mapHeight; j++)
		{
			_grid[i][j].setStatus(0);
			_grid[i][j].setGridVal(1);
		}
}

void Map::setGridVal(const int &w, const int &h, const int &val)
{
	_grid[w][h].setGridVal(val);
}

Grid* Map::getStartGrid()
{
	for (int i = 0; i < _mapWidth; i++)
		for (int j = 0; j < _mapHeight; j++)
			if (_grid[i][j].getGridVal() == GRID_START)
				return &_grid[i][j];
	return nullptr;
}

Grid* Map::getEndGrid()
{
	for (int i = 0; i < _mapWidth; i++)
		for (int j = 0; j < _mapHeight; j++)
			if (_grid[i][j].getGridVal() == GRID_END)
				return &_grid[i][j];
	return nullptr;
}

const int Map::getGridVal(const int &w, const int &h)
{
	return _grid[w][h].getGridVal();
}

const int Map::getWidth()
{
	return _mapWidth;
}

const int Map::getHeight()
{
	return _mapHeight;
}

Grid* Map::getGrid(const int &w, const int &h)
{
	return &_grid[w][h];
}

Grid* Map::getNeighbor(Grid* current, const int &direction)
{
	static int _direction[] = {
		         0, -1,
		-1,  0,          +1,  0,
				 0, +1
	};

	int n_w, n_h;
	n_w = current->getX() + _direction[direction*2];
	n_h = current->getY() + _direction[direction*2 + 1];
	if ( n_w < 0 || n_h < 0 || n_w >= _mapWidth || n_h >= _mapHeight 
		|| _grid[n_w][n_h].getGridVal() == GRID_WALL)
		return nullptr;
	else
		return &_grid[n_w][n_h];
}

void Map::draw(SDL_Renderer *rend, const unsigned short &offsetX, const unsigned short &offsetY)
{
	int maxOffsetX = offsetX + 30;
	int maxOffsetY = offsetY + 30;
	for (int j = offsetX; j < maxOffsetX; j++)
		for (int i = offsetY; i < maxOffsetY; i++)
		{
			SDL_Rect* rect = new SDL_Rect();
			rect->x = _gridWidth * i;
			rect->y = _gridHeight * j;
			rect->h = _gridWidth;
			rect->w = _gridHeight;
			SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
			/*
			if (_grid[i][j].getGridVal() == GRID_FIELD)
				if (_grid[i][j].getStatus() == GRID_STATUS_FREE)
				else if (_grid[i][j].getStatus() == GRID_STATUS_OPEN)
				else 
				*/
			if (_grid[i][j].getGridVal() == GRID_WALL)
			{
				SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
			}
			else if (_grid[i][j].getGridVal() == GRID_END)
			{
				SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
			}
			else if (_grid[i][j].getGridVal() == GRID_START)
			{
				SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
			}
			else if (_grid[i][j].getGridVal() == GRID_PATH)
			{
				SDL_SetRenderDrawColor(rend, 125, 125, 125, 255);
			}
			SDL_RenderFillRect(rend, rect);
			SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
			SDL_RenderDrawRect(rend, rect);
			delete rect;
		}
}

// ================================
void Map::debug_printGrid()
{
	for (int j = 0; j < _mapHeight; j++)
	{
		for (int i = 0; i < _mapWidth; i++)
			std::cout << _grid[i][j].getGridVal() << " ";
		std::cout << std::endl;
	}
}