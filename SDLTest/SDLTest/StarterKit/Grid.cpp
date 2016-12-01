#include "Grid.h"

Grid::Grid()
{
	_status = 0;
}

Grid::~Grid()
{
}

void Grid::setStatus(int stat)
{
	_status = stat;
}

void Grid::setGridVal(int val)
{
	_value = val;
}

void Grid::setH(double H)
{
	_H = H;
}

void Grid::setG(double G)
{
	_G = G;
}

void Grid::setGridCoord(int x, int y)
{
	_x = x;
	_y = y;
}

Grid* Grid::getParent()
{
	return _parentGrid;
}

void Grid::setParent(Grid* parent)
{
	_parentGrid = parent;
}

int Grid::getStatus()
{
	return _status;
}

int Grid::getGridVal()
{
	return _value;
}

int Grid::getX()
{
	return _x;
}
int Grid::getY()
{
	return _y;
}
double Grid::getF()
{
	return (_G + _H);
}

double Grid::getG()
{
	return _G;
}