#include "Map.h"
Map::Map(const Map &obj) {

	_mMapWidth = obj._mMapWidth;
	mMapHeight = obj.mMapHeight;
	mGrid = new Grid*[_mMapWidth];
	for (int i = 0; i < _mMapWidth; i++)
	{
		mGrid[i] = new Grid[mMapHeight];

		for (int j = 0; j < mMapHeight; j++)
		{
			mGrid[i][j] = obj.mGrid[i][j];
		
		}
	}

}


Map::Map(const int &mapWidth, const int &mapHeight, const float &gridWidth, const float &gridHeight, const int &defaultVal) : 
	_mMapWidth(mapWidth), 
	mMapHeight(mapHeight),
	mGridWidth(gridWidth),
	mGridHeight(gridHeight)
{

	mGrid = new Grid*[_mMapWidth];
	for (int i = 0; i < _mMapWidth; i++)
	{
		mGrid[i] = new Grid[mMapHeight];
		for (int j = 0; j < mMapHeight; j++)
		{
			mGrid[i][j].setGridCoord(i, j);
			mGrid[i][j].setGridVal(defaultVal);
		}
	}
	// (width, height)
}

Map::Map(const int &width, const int &height, const int &defaultVal)
{
	_mMapWidth = width;
	mMapHeight = height;
	mGrid = new Grid*[_mMapWidth];
	for (int i = 0; i < _mMapWidth; i++)
	{
		mGrid[i] = new Grid[mMapHeight];
		for (int j = 0; j < mMapHeight; j++)
		{
			mGrid[i][j].setGridCoord(i , j);
			mGrid[i][j].setGridVal(defaultVal);
		}
	}
	// (width, height)
}

Map::~Map()
{
	for (int i = 0; i < _mMapWidth; i++)
		delete[] mGrid[i];
	delete[] mGrid;
}
void Map::generateWall(int wallCount , int spawnRegionOffset, int wallLenght)
{



	for (int i = 0; i < _mMapWidth; i++)
		for (int j = 0; j < mMapHeight; j++)
		{
			//generate border walls
			if (i == 0 || j == 0 || i == mMapHeight - 1 || j == _mMapWidth - 1) {
				mGrid[i][j].setGridVal(GRID_WALL);
			}
		
			
		}

	//generate walls
	std::vector<int> wallPosition;
	int k = 0;
	while (k < wallCount)
	{
		int x = (rand() % (_mMapWidth - spawnRegionOffset * 2)) + spawnRegionOffset;
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
					mGrid[x][y].setGridVal(GRID_WALL);
				}
			}
			else
			{
				for (int y = mMapHeight - wallLenght; y < mMapHeight; y++)
				{

					mGrid[x][y].setGridVal(GRID_WALL);
				}
			}
			k++;
			wallPosition.push_back(x);
		}

		
		
	}
	
}

void Map::resetMap()
{
	for (int i = 0; i < _mMapWidth; i++)
		for (int j = 0; j < mMapHeight; j++)
			if (mGrid[i][j].getGridVal() != 0)
			{
				mGrid[i][j].setStatus(0);
				if (mGrid[i][j].getGridVal() == GRID_PATH)
					mGrid[i][j].setGridVal(GRID_FIELD);

			}
}

void Map::resetStatus()
{
	for (int i = 0; i < _mMapWidth; i++)
		for (int j = 0; j < mMapHeight; j++)
		{
			mGrid[i][j].setStatus(0);
			mGrid[i][j].setParent(NULL);
			mGrid[i][j].setH(0);
			mGrid[i][j].setG(0);
		}
			
}

void Map::reinit()
{
	for (int i = 0; i < _mMapWidth; i++)
		for (int j = 0; j < mMapHeight; j++)
		{
			mGrid[i][j].setStatus(0);
			mGrid[i][j].setGridVal(1);
		}
}

void Map::setGridVal(const int &w, const int &h, const int &val)
{
	mGrid[w][h].setGridVal(val);
}

void Map::setGridWidth(float tilesize)
{
	mGridHeight = tilesize;
	mGridWidth = tilesize;
}

Grid* Map::getStartGrid()
{
	for (int i = 0; i < _mMapWidth; i++)
		for (int j = 0; j < mMapHeight; j++)
			if (mGrid[i][j].getGridVal() == GRID_START)
				return &mGrid[i][j];
	return nullptr;
}

Grid* Map::getEndGrid()
{
	for (int i = 0; i < _mMapWidth; i++)
		for (int j = 0; j < mMapHeight; j++)
			if (mGrid[i][j].getGridVal() == GRID_END)
				return &mGrid[i][j];
	return nullptr;
}

const int Map::getGridVal(const int &w, const int &h)
{
	return mGrid[w][h].getGridVal();
}

const int Map::getWidth()
{
	return _mMapWidth;
}

const int Map::getHeight()
{
	return mMapHeight;
}

Grid* Map::getGrid(const int &w, const int &h)
{
	return &mGrid[w][h];
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
	char gridVal = mGrid[n_w][n_h].getGridVal();
	if ( n_w < 0 || n_h < 0 || n_w >= _mMapWidth || n_h >= mMapHeight 
		|| gridVal == GRID_WALL)
		return nullptr;
	else
		return &mGrid[n_w][n_h];
}

void Map::draw(SDL_Renderer *rend)
{
	Camera *cam = Camera::getInstance();
	unsigned short camPosX = cam->getPosX();
	unsigned short camPosY = cam->getPosY();
	int maxOffsetX = camPosX + cam->getSize();
	int maxOffsetY = camPosY +cam->getSize();
	if (mGrid[29][29].getGridVal() == GRID_WALL)
	{
		int i = 0;
	}
	for (int j = camPosY; j < maxOffsetY; j++)
	{
		for (int i = camPosX; i < maxOffsetX; i++)
		{
			/**/
			SDL_Rect rect = SDL_Rect();
			//translation of 
			rect.x = mGridWidth * i - mGridWidth * camPosX;
			rect.y = mGridHeight * j - mGridWidth * camPosY;
			rect.h = mGridWidth;
			rect.w = mGridHeight;
			if (i == 85)
			{
				int idk = 1;
			}
			/*
			if (_grid[i][j].getGridVal() == GRID_FIELD)
			if (_grid[i][j].getStatus() == GRID_STATUS_FREE)
			else if (_grid[i][j].getStatus() == GRID_STATUS_OPEN)
			else
			*/
			if (mGrid[i][j].getGridVal() == GRID_WALL)
			{
				SDL_SetRenderDrawColor(rend, 125, 125, 125, 255);
			}
			else if (mGrid[i][j].getGridVal() == GRID_END)
			{
				SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);
			}
			else if (mGrid[i][j].getGridVal() == GRID_START)
			{
				SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
			}
			else  if (mGrid[i][j].getGridVal() == GRID_PATH)
			{
				SDL_SetRenderDrawColor(rend, 200, 200, 0, 255);
			}
			else {
				SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
			}
			
			SDL_RenderFillRect(rend, &rect);
			SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
			SDL_RenderDrawRect(rend, &rect);

		}
	}
	

	cam = NULL;
	delete cam;
}

// ================================
void Map::debug_printGrid()
{
	for (int j = 0; j < mMapHeight; j++)
	{
		for (int i = 0; i < _mMapWidth; i++)
			std::cout << mGrid[i][j].getGridVal() << " ";
		std::cout << std::endl;
	}
}
