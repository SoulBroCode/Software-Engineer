#include "Map.h"
Map::Map(const Map &obj) {

	_mapWidth = obj._mapWidth;
	_mapHeight = obj._mapHeight;
	_grid = new Grid*[_mapWidth];
	for (int i = 0; i < _mapWidth; i++)
	{
		_grid[i] = new Grid[_mapHeight];

		for (int j = 0; j < _mapHeight; j++)
		{
			_grid[i][j] = obj._grid[i][j];
		
		}
	}

}


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
void Map::generateWall(int wallCount , int spawnRegionOffset, int wallLenght)
{



	for (int i = 0; i < _mapWidth; i++)
		for (int j = 0; j < _mapHeight; j++)
		{
			//generate border walls
			if (i == 0 || j == 0 || i == _mapHeight - 1 || j == _mapWidth - 1) {
				_grid[i][j].setGridVal(GRID_WALL);
			}
		
			
		}

	//generate walls
	std::vector<int> wallPosition;
	int k = 0;
	while (k < wallCount)
	{
		int x = (rand() % (_mapWidth - spawnRegionOffset * 2)) + spawnRegionOffset;
		bool nextToOtherWall = false;
		for (int i = 0; i < wallPosition.size(); i++)
		{
			if (x == wallPosition[i] || x == wallPosition[i] - 1 || x == wallPosition[i] + 1) {
				nextToOtherWall = true;
			}
		
		}
		if (!nextToOtherWall)
		{
			if (rand() % 2 == 0)
			{
				for (int y = 1; y < wallLenght; y++)
				{
					_grid[x][y].setGridVal(GRID_WALL);
				}
			}
			else
			{
				for (int y = _mapHeight - wallLenght; y < _mapHeight; y++)
				{

					_grid[x][y].setGridVal(GRID_WALL);
				}
			}
			k++;
			wallPosition.push_back(x);
		}

		
		
	}
	
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

void Map::resetStatus()
{
	for (int i = 0; i < _mapWidth; i++)
		for (int j = 0; j < _mapHeight; j++)
			_grid[i][j].setStatus(0);
			
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

void Map::setGridWidth(float tilesize)
{
	_gridHeight = tilesize;
	_gridWidth = tilesize;
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
	char gridVal = _grid[n_w][n_h].getGridVal();
	if ( n_w < 0 || n_h < 0 || n_w >= _mapWidth || n_h >= _mapHeight 
		|| gridVal == GRID_WALL)
		return nullptr;
	else
		return &_grid[n_w][n_h];
}

void Map::draw(SDL_Renderer *rend)
{
	Camera *cam = Camera::getInstance();
	unsigned short camPosX = cam->getPosX();
	unsigned short camPosY = cam->getPosY();
	int maxOffsetX = camPosX + cam->getSize();
	int maxOffsetY = camPosY +cam->getSize();
	
	for (int j = camPosY; j < maxOffsetY; j++)
	{
		for (int i = camPosX; i < maxOffsetX; i++)
		{
			/**/
			SDL_Rect rect = SDL_Rect();
			//translation of 
			rect.x = _gridWidth * i - _gridWidth * camPosX;
			rect.y = _gridHeight * j - _gridWidth * camPosY;
			rect.h = _gridWidth;
			rect.w = _gridHeight;
			
			/*
			if (_grid[i][j].getGridVal() == GRID_FIELD)
			if (_grid[i][j].getStatus() == GRID_STATUS_FREE)
			else if (_grid[i][j].getStatus() == GRID_STATUS_OPEN)
			else
			*/
			if (_grid[i][j].getGridVal() == GRID_WALL)
			{
				SDL_SetRenderDrawColor(rend, 125, 125, 125, 255);
			}
			else if (_grid[i][j].getGridVal() == GRID_END)
			{
				SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
			}
			else if (_grid[i][j].getGridVal() == GRID_START)
			{
				SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
			}
			else  if (_grid[i][j].getGridVal() == GRID_PATH)
			{
				SDL_SetRenderDrawColor(rend, 200, 200, 0, 255);
			}
			else {
				SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
			}
			
			SDL_RenderFillRect(rend, &rect);
			SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		

		}
	}
	

	cam = NULL;
	delete cam;
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
