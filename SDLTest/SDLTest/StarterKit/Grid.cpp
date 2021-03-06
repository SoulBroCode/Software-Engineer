#include "Grid.h"
Grid::Grid(const Grid &obj) {
	_status = obj._status;
	_value = obj._value;
	_x = obj._x;
	_y = obj._y;

	Grid* _parentGrid =nullptr;
	
	_G = obj._G;
	_H = obj._H;
}



Grid::Grid()
{
	_status = 0;
}
Grid::Grid(short x, short y) :
	_status(0),
	_x(x),
	_y(y),
	_value(0)
{

}

Grid::~Grid()
{
}



void Grid::init(short x, short y)
{
	_x = x;
	_y = y;
}

void Grid::setStatus(const char &stat)
{
	_status = stat;
}

void Grid::setGridVal(const char &val)
{
	_value = val;
}

void Grid::setH(const float &H)
{
	_H = H;
}

void Grid::setG(const float &G)
{
	_G = G;
}

void Grid::setGridCoord(const int &x, const int &y)
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

const char Grid::getStatus()
{
	return _status;
}

const char Grid::getGridVal()
{
	return _value;
}

const short Grid::getX()
{
	return _x;
}
const short Grid::getY()
{
	return _y;
}
const float Grid::getF()
{
	return (_G + _H);
}

const float Grid::getG()
{
	return _G;
}